#include "../common.h"

#include <fstream>
#include <sstream>
#include <set>
#include <cxxabi.h>

#include "llvm/Pass.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

struct SafeDispatchIns : public ModulePass {
  static char ID;
  const std::string checkFunctionStr = "check(int, void*)";
  const std::string insertFunctionStr = "insert(int, void*)";
  Function * insertFunctionPtr, * checkFunctionPtr, * mainPointer;

  std::set<std::string> VMethodSet;
  std::map<int, std::set<std::string>> IntToMethods;
  std::map<std::string, Function *> MethodToMethodsPtr;

  SafeDispatchIns();
  void loadValidM(std::string path);
  bool runOnModule(Module &) override;
  bool findFunctions(Module &M);
  bool performInsert(Module &M);
  void insertInsert(int num, Function * functionPtr);
  bool instrumentCheck(Module &M);
  bool dealWithIndirectCall(CallInst*);
};

/*
 * Tool
 * for a line splited with *delim*
 */
inline void split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
      elems.push_back(item);
  }
}

/*
 * takes Function.getName()
 * output Function's real name
 */
inline std::string demangle(const char* name){
  int status = -1;
  std::unique_ptr<char, void(*)(void*)> res { abi::__cxa_demangle(name, NULL, NULL, &status), std::free };
  return (status == 0) ? res.get() : std::string(name);
}

// Global Pass Registry
char SafeDispatchIns::ID = 0;

/*
 * Constructor
 */
SafeDispatchIns::SafeDispatchIns() : ModulePass(ID) {
  errs() << "Running SafeDispatchIns...\n";
  const std::string validMPath = "./build/validm.config";
  loadValidM(validMPath);
}

/*
 * Load ValidM from file
 */
void SafeDispatchIns::loadValidM(std::string validMPath) {
  std::ifstream validMFile(validMPath);
  std::string line, item;
  while(std::getline(validMFile, line)){
    std::vector<std::string> rowValues;
    split(line, '\t', rowValues);
    for(int i = 1;i < rowValues.size();i++){
      IntToMethods[std::stoi(rowValues[0])].insert(rowValues[i]);
      VMethodSet.insert(rowValues[i]);
    }
  }
    validMFile.close();
}

bool SafeDispatchIns::runOnModule(Module &M) {
  // find all functions
  // including insert, check
  // and all vmethods
  if(!findFunctions(M))
    return false;
  #ifdef CUSTOM_DEBUG
  // print for debugging
  for(Function &F : M)
    errs() << F.getName() << '\n';
  #endif

  // Instrumentation 1: insert pointer  vmethods' addresses
  if(!performInsert(M))
    return false;
  // Instrumentation 2: modify 'check' function
  if(!instrumentCheck(M))
    return false;
  return true;
}

/*
 * iterate over all Instructions
 * to find the pre-instrumented check(int, void*)
 */
bool SafeDispatchIns::instrumentCheck(Module &M){
  for(Function &F : M){
    // 1) find the CallInst to check(int, void*)
    for (inst_iterator i = inst_begin(F), e = inst_end(F); i != e; i++){
      if (CallInst * callInst = dyn_cast<CallInst>(&(*i))) {
        if(callInst->getCalledFunction() == checkFunctionPtr){
          #ifdef CUSTOM_DEBUG
          errs() << "Find CallInst calling check\n";
          #endif
          dealWithIndirectCall(callInst);
        }
      }
    }
  }
  return true;
}

/*
 * Deal with indirect call section
 * takes in the instruction which calls check(int, void*)
 * there should be six unimportant instructions
 * between call check(int,void*) and the final indirect call.
 * We need to move 'check(int, void*)' to the position
 * just before the indirect call,
 * and refill the second argument value.
 */
bool SafeDispatchIns::dealWithIndirectCall(CallInst * checkCall){
  // get all seven instructions
  Instruction * i1 = checkCall->getNextNonDebugInstruction();
  if(!i1) return false;
  Instruction * i2 = i1->getNextNonDebugInstruction();
  if(!i2) return false;
  Instruction * i3 = i2->getNextNonDebugInstruction();
  if(!i3) return false;
  Instruction * i4 = i3->getNextNonDebugInstruction();
  if(!i4) return false;
  Instruction * i5 = i4->getNextNonDebugInstruction();
  if(!i5) return false;
  Instruction * icall = i5->getNextNonDebugInstruction();
  if(!icall) return false;
  CallInst * icallInst = dyn_cast<CallInst>(icall);
  if(!icallInst) return false;
  #ifdef CUSTOM_DEBUG
  checkCall->dump();
  i1->dump();
  i2->dump();
  i3->dump();
  i4->dump();
  i5->dump();
  icallInst->dump();
  #endif
  // insert a bitcast after i5, before check
  IRBuilder<> builder(checkCall->getContext());
  builder.SetInsertPoint(icallInst);
  Value * callTarget = builder.CreateBitCast(
    icallInst->getCalledValue(),
    Type::getInt8PtrTy(checkCall->getContext())
  );
  // move check to the position just before icall
  checkCall->moveBefore(icallInst);
  // set the second argument to be the icall target
  checkCall->setArgOperand(1, callTarget);
  return true;
}

/*
 * Iterate over all functions
 * to find 'check(int, void*)', 'insert(int, void*)'
 * and all vmethods in ValidM
 * return false if one of them are not found
 */
bool SafeDispatchIns::findFunctions(Module &M){
  // find all vmethods and store their pointer
  for(Function &F : M){
    std::string functionName = demangle(F.getName().str().c_str());
    if(functionName == insertFunctionStr){
      insertFunctionPtr = &F;
      continue;
    }
    if(functionName == checkFunctionStr){
      checkFunctionPtr = &F;
      continue;
    }
    if(functionName == "main"){
      mainPointer = &F;
      continue;
    }
    if(VMethodSet.find(functionName) == VMethodSet.end())
      // not the function we wanna protect
      continue;
    MethodToMethodsPtr[functionName] = &F;
    #ifdef CUSTOM_DEBUG
    errs() << functionName << " found!\n";
    #endif
  }
  // check 'insert' and 'main'
  if(!insertFunctionPtr){
    errs() << "Function insert(int, void*) not found.\n";
    return false;
  }
  if(!checkFunctionPtr){
    errs() << "Function check(int, void*) not found.\n";
    return false;
  }
  if(!mainPointer){
    errs() << "Function main not found.\n";
    return false;
  }
  return true;
}

/*
 * Insert pair of <int, Function *>
 * into checking module
 * at the very beginning of Function main()
 * return false if one of vmethods in ValidM are not found in IR
 */
bool SafeDispatchIns::performInsert(Module &M){
  // insert 'insert' function
  for(auto i = IntToMethods.begin(), e = IntToMethods.end();
    i != e;
    i++){
    for(std::string functionNameStr : i->second){
      if(MethodToMethodsPtr.find(functionNameStr) == MethodToMethodsPtr.end()){
        errs() << "Cannot find " << functionNameStr << " in IR\n";
        return false;
      }
      this->insertInsert(i->first, MethodToMethodsPtr[functionNameStr]);
    }
  }
  return true;
}

/*
 * Insert 'insert(int, void*)' at the beginning of Function main()
 */
void SafeDispatchIns::insertInsert(int num, Function * functionPtr){
  BasicBlock * entryBlock = &(mainPointer->getEntryBlock());
  IRBuilder<> builder(&(entryBlock->front()));

  ConstantInt * numValue = ConstantInt::get(Type::getInt32Ty(mainPointer->getContext()),num);
  Value * pointToAddress = builder.CreateBitCast(functionPtr, Type::getInt8PtrTy(mainPointer->getContext()));
  CallInst * callInst = builder.CreateCall(insertFunctionPtr, { numValue, pointToAddress });
}



static RegisterPass<SafeDispatchIns> X("SafeDispatchIns", "Instrumentation of SafeDispatch",
                                    false,
                                    false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new SafeDispatchIns()); });
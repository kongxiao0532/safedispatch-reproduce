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

using namespace llvm;

struct InsertMethodAddrPass : public ModulePass {
    static char ID;
    const std::string checkFunctionStr = "check(int, void*)";
    const std::string insertFunctionStr = "insert(int, void*)";
    Function * insertFunctionPrt, * mainPointer;

    std::set<std::string> VMethodSet;
    std::map<int, std::set<std::string>> IntToMethods;

    InsertMethodAddrPass();
    bool runOnModule(Module &) override;
    void loadValidM(std::string path);
    void insertInsert(int num, Function * functionPtr);
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
char InsertMethodAddrPass::ID = 0;

/*
 * Constructor
 */
InsertMethodAddrPass::InsertMethodAddrPass() : ModulePass(ID) {
    errs() << "Running InsertMethodAddrPass...\n";
    const std::string validMPath = "./build/validm.config";
    loadValidM(validMPath);
}

/*
 * Load ValidM from file
 */
void InsertMethodAddrPass::loadValidM(std::string validMPath) {
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

bool InsertMethodAddrPass::runOnModule(Module &M) {
    // get insert(int, void*)
    for(Function &F : M)
      errs() << F.getName() << '\n';

    // find all vmethods and store thier pointer
    std::map<std::string, Function *> MethodToMethodsPtr;
    for(Function &F : M){
      std::string functionName = demangle(F.getName().str().c_str());
      if(functionName == insertFunctionStr){
        insertFunctionPrt = &F;
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
    if(!insertFunctionPrt){
      errs() << "fFunction insert(int, void*) not found.\n";
      return false;
    }
    if(!mainPointer){
      errs() << "Function main not found.\n";
      return false;
    }
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

void InsertMethodAddrPass::insertInsert(int num, Function * functionPtr){
    BasicBlock * entryBlock = &(mainPointer->getEntryBlock());
    IRBuilder<> builder(&(entryBlock->front()));

    ConstantInt * numValue = ConstantInt::get(Type::getInt32Ty(mainPointer->getContext()), num);
    Value * pointToAddress = builder.CreateBitCast(functionPtr, Type::getInt8PtrTy(mainPointer->getContext()));
    CallInst * callInst = builder.CreateCall(insertFunctionPrt, { numValue, pointToAddress });
    #ifdef CUSTOM_DEBUG
    callInst->dump();
    #endif
}



static RegisterPass<InsertMethodAddrPass> X("InsertMethodAddrPass", "Instrumentation 2 of SafeDispatch",
                                    false,
                                    false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new InsertMethodAddrPass()); });
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

struct CheckCallAddrPass : public ModulePass {
  static char ID;
  const std::string checkFunctionStr = "check(int, void*)";
  Function * checkFunctionPtr, * mainPointer;


  CheckCallAddrPass();
  bool runOnModule(Module &) override;
};

/*
 * takes Function.getName()
 * output Function's real name
 */
inline std::string demangle(const char* name){
  int status = -1;
  std::unique_ptr<char, void(*)(void*)> res { abi::__cxa_demangle(name, NULL, NULL, &status), std::free };
  return (status == 0) ? res.get() : std::string(name);
}


/*
 * Constructor
 */
CheckCallAddrPass::CheckCallAddrPass() : ModulePass(ID) {
    errs() << "Running CheckCallAddrPass...\n";
}

bool CheckCallAddrPass::runOnModule(Module &M) {
  // 1) find Function check(int, void*)
  for(Function &F : M){
      std::string functionName = demangle(F.getName().str().c_str());
      if(functionName == checkFunctionStr){
        checkFunctionPtr = &F;
        break;
      }
    }
  // check 'check'
  if(!checkFunctionPtr){
    errs() << "Function check(int, void*) not found.\n";
    return false;
  }
  for(Function &F : M){
    // 1) find the CallInst to check(int, void*)
    for (inst_iterator i = inst_begin(F), e = inst_end(F); i != e; i++){
      if (CallInst * callInst = dyn_cast<CallInst>(&(*i))) {
        if(callInst->getCalledFunction() == checkFunctionPtr)
          errs() << "Find CallInst calling check\n";
      }
    }
  }
  return true;
}


static RegisterPass<CheckCallAddrPass> X("CheckCallAddrPass",
   "Instrumentation 3 of SafeDispatch", false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new CheckCallAddrPass()); });
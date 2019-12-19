#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {

    struct SafeDispatchIns : public ModulePass {
        static char ID;

        SafeDispatchIns();
        bool runOnModule(Module &M) override;

        void loadValidM(std::string path);
    };
}

SafeDispatchIns::SafeDispatchIns() : ModulePass(ID) {
    const std::string validMPath = "/home/guest/llvm-project/cpptest/validm.json";
    // loadValidM(validMPath);
}


bool SafeDispatchIns::runOnModule(Module &M) {
    outs() << "Running SafeDispatchIns...\n";
    
    return true;
};

// void loadValidM(std::string path){

// }

// Global Pass Registry
char SafeDispatchIns::ID = 0;
static RegisterPass<SafeDispatchIns> X("SafeDispatchIns", "Instrumentation of SafeDispatch",
                                    false,
                                    false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new SafeDispatchIns()); });
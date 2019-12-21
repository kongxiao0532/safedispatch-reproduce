#include "CHAVisitor.h"

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
# include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"
using namespace clang;



// AST Consumer
class FindNamedClassConsumer : public clang::ASTConsumer {
  CompilerInstance &Instance;
  std::set<std::string> ParsedTemplates;
public:
  FindNamedClassConsumer(CompilerInstance &Instance,
                       std::set<std::string> ParsedTemplates)
    : Instance(Instance), ParsedTemplates(ParsedTemplates) {}


  void HandleTranslationUnit(ASTContext& context) override {
    CHAVisitor v(&context);
    v.TraverseDecl(context.getTranslationUnitDecl());
    v.CalculateValidTables();
  }
};

// AST Action
class FindNamedClassAction : public PluginASTAction {
  std::set<std::string> ParsedTemplates;
protected:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                               llvm::StringRef) override {
    return llvm::make_unique<FindNamedClassConsumer>(CI, ParsedTemplates);
  }

// parse arguments
  bool ParseArgs(const CompilerInstance &CI,
                const std::vector<std::string> &args) override {
    for (unsigned i = 0, e = args.size(); i != e; ++i) {
      #ifdef CUSTOM_DEBUG
      llvm::errs() << "PrintFunctionNames arg = " << args[i] << "\n";
      #endif

      // Example error handling.
      DiagnosticsEngine &D = CI.getDiagnostics();
      if (args[i] == "-an-error") {
        unsigned DiagID = D.getCustomDiagID(DiagnosticsEngine::Error,
                                            "invalid argument '%0'");
        D.Report(DiagID) << args[i];
        return false;
      } else if (args[i] == "-parse-template") {
        if (i + 1 >= e) {
          D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                    "missing -parse-template argument"));
          return false;
        }
        ++i;
        ParsedTemplates.insert(args[i]);
      }
    }
    if (!args.empty() && args[0] == "help")
      PrintHelp(llvm::errs());

    return true;
  }
  void PrintHelp(llvm::raw_ostream& ros) {
    ros << "Help for PrintClassNames plugin goes here\n";
  }

};


static FrontendPluginRegistry::Add<FindNamedClassAction>
X("ClassHierachyAnalysis", "ClassHierachyAnalysis");

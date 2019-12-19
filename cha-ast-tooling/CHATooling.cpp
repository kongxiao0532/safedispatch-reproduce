#include "CHAVisitor.h"



// AST Consumer
class FindNamedClassConsumer : public clang::ASTConsumer {
  CompilerInstance &Instance;
  std::set<std::string> ParsedTemplates;
public:
  FindNamedClassConsumer(CompilerInstance &Instance,
      Rewriter * rewriter) : Instance(Instance), rewriter(rewriter) {}

  Rewriter * rewriter;

  void HandleTranslationUnit(ASTContext& context) override {
    CHAVisitor v(&context, rewriter);
    v.TraverseDecl(context.getTranslationUnitDecl());
    v.CalculateValidTables();
  }
};


int main(int argc, char *argv[]) {
  if (argc != 2) {
    llvm::outs() << "Usage: ./CHATooling <filename>\n";
    return 1;
  }

  // CompilerInstance will hold the instance of the Clang compiler for us,
  // managing the various objects needed to run the compiler.
  CompilerInstance compilerInstance;
  compilerInstance.createDiagnostics();

  LangOptions &lo = compilerInstance.getLangOpts();
  lo.CPlusPlus = 1;

  // Initialize target info with the default triple for our platform.
  auto TO = std::make_shared<TargetOptions>();
  TO->Triple = llvm::sys::getDefaultTargetTriple();
  TargetInfo *TI =
      TargetInfo::CreateTargetInfo(compilerInstance.getDiagnostics(), TO);
  compilerInstance.setTarget(TI);

  compilerInstance.createFileManager();
  FileManager &FileMgr = compilerInstance.getFileManager();
  compilerInstance.createSourceManager(FileMgr);
  SourceManager &sourceManager = compilerInstance.getSourceManager();
  compilerInstance.createPreprocessor(TU_Module);
  compilerInstance.createASTContext();

  // A Rewriter helps us manage the code rewriting task.
  Rewriter rewriter;
  rewriter.setSourceMgr(sourceManager, compilerInstance.getLangOpts());

  // Set the main file handled by the source manager to the input file.
  const FileEntry *FileIn = FileMgr.getFile(argv[1]);
  sourceManager.setMainFileID(
      sourceManager.createFileID(FileIn, SourceLocation(), SrcMgr::C_User));
  compilerInstance.getDiagnosticClient().BeginSourceFile(
      compilerInstance.getLangOpts(), &compilerInstance.getPreprocessor());

  // Create an AST consumer instance which is going to get called by
  // ParseAST.
  FindNamedClassConsumer consumer(compilerInstance, &rewriter);

  // Parse the file to AST, registering our consumer as the AST consumer.
  ParseAST(compilerInstance.getPreprocessor(), &consumer,
           compilerInstance.getASTContext());

  // At this point the rewriter's buffer should be full with the rewritten
  // file contents.
  const RewriteBuffer *RewriteBuf =
      rewriter.getRewriteBufferFor(sourceManager.getMainFileID());
  llvm::outs() << std::string(RewriteBuf->begin(), RewriteBuf->end());

  return 0;
}
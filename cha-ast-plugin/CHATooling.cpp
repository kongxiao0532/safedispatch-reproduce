#include "CHAVisitor.h"
#include "InstVisitor.h"

#include <iostream>
#include <fstream>


std::string instrumentedFileName = "./build/instrumented.cpp";
std::string validMOutputFileName = "./build/validm.config";

// AST Consumer
class FindNamedClassConsumer : public clang::ASTConsumer {
  CompilerInstance &Instance;
  std::set<std::string> ParsedTemplates;
public:
  FindNamedClassConsumer(CompilerInstance &Instance,
      Rewriter * rewriter) : Instance(Instance), rewriter(rewriter) {}

  Rewriter * rewriter;
  // ValidM
  std::map<CXXRecordDecl *,
    std::map<std::string, std::set<CXXMethodDecl *>>> ValidM;
  std::map<CXXRecordDecl *,
    std::map<std::string, int>> ValidMInt;
  std::map<int, std::set<std::string>> IntToMethods;

  void HandleTranslationUnit(ASTContext& context) override {
    // CHA Visitor to build ValidM
    CHAVisitor cv(&context);
    cv.TraverseDecl(context.getTranslationUnitDecl());
    cv.CalculateValidTables();
    this->ValidM = cv.getValidM();
    // calculate IntToMethods
    TransformValidM();
    // write IntToMethods into file
    outputIntToMethods();
    // Instrument 'check'
    InstVisitor iv(&context, rewriter, ValidMInt);
    iv.TraverseDecl(context.getTranslationUnitDecl());
  }

  /*
   * Takes ValidM
   * Assign a $i_{(c,n)}$ for every <class, method_name>
   * Calculate ValidMInt & InToMethods
   */
  void TransformValidM(){
    int pool = 1, assigned;
    for(auto i1 = ValidM.begin(), e1 = ValidM.end();
      i1 != e1;
      i1++){
      for(auto i2 = i1->second.begin(), e2 = i1->second.end();
        i2 != e2;
        i2++){
        // for a <CXXRecordDecl *, string>
        assigned = pool++;
        ValidMInt[i1->first][i2->first] = assigned;
        for(CXXMethodDecl * CMD : i2->second){
          IntToMethods[assigned].insert(GetFunctionAsString(CMD, true, true));
        }
      }
    }
  }

  /*
   * Output ValidM into file
   * num,{string,string,...}
   */
  void outputIntToMethods(){
    std::ofstream validMFile;
    validMFile.open(validMOutputFileName);
    for(auto i = IntToMethods.begin(), e = IntToMethods.end();
      i != e;
      i++){
      validMFile << i->first;
      for(std::string str : i->second){
        validMFile << '\t' << str;
      }
      validMFile << "\n";
    }
    validMFile.close();
  }

  /*
  * Return a Function's as a string
  * Including FunctionName and parameter type
  * e.g. "m1(int,float)"
  */
  std::string GetFunctionAsString(CXXMethodDecl * CMD, bool Qualified, bool WithParams){
    std::string result = Qualified ? CMD->getQualifiedNameAsString() : CMD->getNameAsString();
    if(WithParams){
      result += "(";
      for(auto i = CMD->param_begin(), e = CMD->param_end();
      i != e;
      i++) {
        const ParmVarDecl * PVD = *i;
        if(*(result.end() - 1) != '(')
          result += ",";
        result += PVD->getOriginalType().getAsString();
      }
      result += ")";
    }
    return result;
  }

};


int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    llvm::outs() << "Usage: ./CHATooling <filename> [<output_filename>]\n";
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
  auto fileID = sourceManager.createFileID(FileIn, SourceLocation(), SrcMgr::C_User);
  sourceManager.setMainFileID(fileID);
  compilerInstance.getDiagnosticClient().BeginSourceFile(
      compilerInstance.getLangOpts(), &compilerInstance.getPreprocessor());


  // insert #include
  std::stringstream stream;
  stream << "extern void safepatch::check(int , void * );\n";
  rewriter.InsertText(sourceManager.getComposedLoc(fileID, 0), stream.str(), true, true);

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

  // write instrumented code out
  std::ofstream instrumentedFile;
  if(argc == 3)
    instrumentedFileName = argv[2];
  instrumentedFile.open(instrumentedFileName);
  instrumentedFile << std::string(RewriteBuf->begin(), RewriteBuf->end());
  instrumentedFile.close();
  llvm::outs() << "Instrumented file has been output to " << instrumentedFileName << "\n";
  llvm::outs() << "ValidM has been output to " << validMOutputFileName << "\n";
  return 0;
}
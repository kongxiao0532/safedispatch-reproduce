#include "InstVisitor.h"

bool InstVisitor::VisitCXXMemberCallExpr(CXXMemberCallExpr * CMCE){
  // only deal with virtual methods
  if(!CMCE->getMethodDecl() || !CMCE->getMethodDecl()->isVirtual()){
    return true;
  }
  #ifdef CUSTOM_DEBUG
  if(CMCE->getMethodDecl() != nullptr){
    llvm::outs() << "Inside CXXMemberCallExpr: " <<
      CMCE->getObjectType().getAsString();
    llvm::outs() << CMCE->getMethodDecl()->getNameAsString() << '\n';
  }else{
    // TODO: function pointer
    llvm::outs() << "Inside CXXMemberCallExpr via Function Pointers: " <<
      CMCE->getObjectType().getAsString();
  }
  #endif
  int assigned =
    ValidMInt[CMCE->getRecordDecl()][CMCE->getMethodDecl()->getNameAsString()];
  // insert code
  std::stringstream stream;
  stream << "// check function " <<
    CMCE->getObjectType().getAsString() << "::" <<
    CMCE->getMethodDecl()->getNameAsString() << "\n";
  stream << "check(" << assigned << ", nullptr);\n";
  SourceLocation ST = CMCE->getSourceRange().getBegin();
  rewriter->InsertText(ST, stream.str(), true, true);
  return true;
}

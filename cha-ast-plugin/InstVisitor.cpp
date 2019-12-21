#include "InstVisitor.h"

bool InstVisitor::VisitCXXMemberCallExpr(CXXMemberCallExpr * CMCE){
  // only deal with virtual methods
  if(!CMCE->getMethodDecl() || !CMCE->getMethodDecl()->isVirtual()){
    return true;
  }
  // only deal with dyanmic calls
  if(!CMCE->getImplicitObjectArgument()->getType().mayBeDynamicClass()){
    return true;
  }
  // MemberExpr * ME = dyn_cast<MemberExpr>(CMCE->getCallee());
  // if(!ME)
  //   return true;
  // if(ME->getImplicitObjectArgument())
  #ifdef CUSTOM_DEBUG
  if(CMCE->getMethodDecl() != nullptr){
    llvm::errs() << "Inside CXXMemberCallExpr: " <<
      CMCE->getObjectType().getAsString();
    llvm::errs() << CMCE->getMethodDecl()->getNameAsString() << '\n';
  }else{
    // TODO: function pointer
    llvm::errs() << "Inside CXXMemberCallExpr via Function Pointers: " <<
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

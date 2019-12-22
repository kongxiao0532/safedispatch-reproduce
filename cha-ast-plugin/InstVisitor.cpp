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
    ValidMInt[CMCE->getRecordDecl()][GetFunctionAsString(CMCE->getMethodDecl(), false, VALIDM_WITH_PARAMS)];
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

/*
 * Return a Function's as a string
 * Including FunctionName and parameter type
 * e.g. "m1(int,float)"
 */
std::string InstVisitor::GetFunctionAsString(CXXMethodDecl * CMD, bool Qualified, bool WithParams){
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
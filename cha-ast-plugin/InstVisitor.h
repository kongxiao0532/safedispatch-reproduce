#include "../common.h"

#include <sstream>
#include <string>

#include "clang/AST/AST.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Sema/Sema.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"
using namespace clang;


class InstVisitor : public RecursiveASTVisitor<InstVisitor> {

  ASTContext * Context;
  Rewriter * rewriter;
  std::map<CXXRecordDecl *,
    std::map<std::string, int>> ValidMInt;


public:
  InstVisitor(ASTContext *Context, Rewriter * rewriter,
    std::map<CXXRecordDecl *, std::map<std::string, int>> &ValidMInt)
      : Context(Context), rewriter(rewriter), ValidMInt(ValidMInt) {}

  bool VisitCXXMemberCallExpr(CXXMemberCallExpr * CMCE);
  std::string GetFunctionAsString(CXXMethodDecl * CMD, bool Qualified, bool WithParams);

private:
};
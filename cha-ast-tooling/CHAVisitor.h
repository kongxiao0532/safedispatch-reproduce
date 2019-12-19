
#include "clang/Frontend/FrontendPluginRegistry.h"
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

#define CUSTOM_DEBUG 0

class CHAVisitor : public RecursiveASTVisitor<CHAVisitor> {

  Rewriter * rewriter;
  ASTContext *Context;
  /* maps class to its subclasses (including itself as a subclass) */
  std::map<CXXRecordDecl *, std::set<CXXRecordDecl *>> ClassSubclassMap;
  /* maps class to its multi-layer subclasses (including itself as a subclass) */
  std::map<CXXRecordDecl *, std::set<CXXRecordDecl *>> ClassMultiSubclassMap;
  /* maps class to its original virtual methods and its name */
  std::map<CXXRecordDecl *, std::set<CXXMethodDecl *>> ClassOriginalVMethodPtrMap;
  /*
   * str version is for matching in CHAVisitor::CalculateInheritedVMethod()
   * These are unqualified names with parameters.  e.g. "m1(int)"
   */
  std::map<CXXRecordDecl *, std::set<std::string>> ClassOriginalVMethodStrMap;
  /* maps class to its virtual methods inherited from its base classes */
  std::map<CXXRecordDecl *, std::set<CXXMethodDecl *>> ClassInheritedVMethodPtrMap;
  /*
   * str version is for matching in CHAVisitor::CalculateInheritedVMethod()
   * These are unqualified names with parameters.  e.g. "m1(int)"
   */
  std::map<CXXRecordDecl *, std::set<std::string>> ClassInheritedVMethodStrMap;

  std::map<CXXRecordDecl *,
    std::map<std::string, std::set<CXXMethodDecl *>>> ValidM;
  // TODO: ValidVT;


public:
  CHAVisitor(ASTContext * Context, Rewriter * rewriter) : Context(Context), rewriter(rewriter) {}

  bool VisitCXXRecordDecl(CXXRecordDecl * CRD);

private:
  void PrintClass(CXXRecordDecl * CRD);
  void PrintBaseClass(CXXRecordDecl * CRD);
  void PrintVirtualMethod(CXXRecordDecl * CRD);
  std::string GetFunctionAsString(CXXMethodDecl * FD, bool Qualified, bool WithParams);
  void CalculateAllSubclass();
  void CalculateInheritedVMethod();
  std::vector<std::string> FindAllVMethodString(CXXRecordDecl * CRD, bool Qualified, bool WithParams);
  std::vector<CXXMethodDecl *> FindAllVMethodPointer(CXXRecordDecl * CRD);
  std::vector<CXXMethodDecl *> FindVMethodPointer(CXXRecordDecl * CRD, std::string MethodName);
  void CalculateValidM();

  #ifdef CUSTOM_DEBUG
  void printValidM();
  #endif
  // void CalculateValidVT();
public:
  void CalculateValidTables();
  std::map<CXXRecordDecl *, std::map<std::string, std::set<CXXMethodDecl *>>> getValidM();
};
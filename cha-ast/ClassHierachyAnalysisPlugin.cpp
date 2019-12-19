//===- PrintFunctionNames.cpp ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Example clang plugin which simply prints the names of all the top-level decls
// in the input file.
//
//===----------------------------------------------------------------------===//

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
# include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"
using namespace clang;

#define CUSTOM_DEBUG 0

namespace {
  class CHAVisitor : public RecursiveASTVisitor<CHAVisitor> {

    const std::set<std::string> &ParsedTemplates;
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
    CHAVisitor(const std::set<std::string> &ParsedTemplates,
      ASTContext *Context)
        : ParsedTemplates(ParsedTemplates), Context(Context) {}

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

  /*
   * At every C++ class definition
   * Push the class pointer into the subclass list of its base class
   */
  bool CHAVisitor::VisitCXXRecordDecl(CXXRecordDecl *CRD){
    // a CPP class
    #ifdef CUSTOM_DEBUG
    this->PrintClass(CRD);
    this->PrintBaseClass(CRD);
    this->PrintVirtualMethod(CRD);
    #endif
    // iterate its BASE Classes
    for(auto i = CRD->bases_begin(),
      e = CRD->bases_end();
      i != e;
      i++) {
      CXXRecordDecl *BaseCRD = i->getType()->getAsCXXRecordDecl();
      // push CRD into its base class's subclass list
      ClassSubclassMap[BaseCRD].insert(CRD);
    }
    // iterate its virtual methods
    for(auto i = CRD->method_begin(),
      e = CRD->method_end();
      i != e;
      i++) {
      Decl *D = *i;
      if(CXXMethodDecl *CMD = dyn_cast<CXXMethodDecl>(D)){
        if(CMD->isVirtual()){
          ClassOriginalVMethodPtrMap[CRD].insert(CMD);
          ClassOriginalVMethodStrMap[CRD].insert(this->GetFunctionAsString(CMD, false, true));
        }
      }
    }
    // push itself into its subclass list
    ClassSubclassMap[CRD].insert(CRD);
    return true;
  }


  /*
   * public interface for ValidM and ValidVT calculation
   */
  void CHAVisitor::CalculateValidTables() {
    // First, calculate the full hierachy
    // including subclasses and inherited virtual methods
    CalculateAllSubclass();
    CalculateInheritedVMethod();
    this->CalculateValidM();
    // TODO: this->CalculateValidVT();
    #ifdef CUSTOM_DEBUG
    // print ValidM
    printValidM();
    #endif
  }

#ifdef CUSTOM_DEBUG
    void CHAVisitor::printValidM(){
      llvm::outs() << "Outputting ValidM:\n";
      for(auto i1 = ValidM.begin(), e1 = ValidM.end(); i1 != e1; i1++){
        llvm::outs() << i1->first->getNameAsString();
        for(auto i2 = i1->second.begin(), e2 = i1->second.end(); i2 != e2; i2++){
          llvm::outs() << '\t' << i2->first << ": ";
          for(CXXMethodDecl * Method : i2->second){
            llvm::outs() << this->GetFunctionAsString(Method, true, true) << ", ";
          }
        }
        llvm::outs() << '\n';
      }
    }
#endif

  /*
   * public interface for getting ValidM
   */
  std::map<CXXRecordDecl *, std::map<std::string, std::set<CXXMethodDecl *>>> CHAVisitor::getValidM() {
    return ValidM;
  }

  /*
   * Calculate ValidM
   * ValidM[CLASS][METHOD]
   * = {VMethods of CLASS + VMethods inherited from the parents of CLASS + VMethods of subclasses of CLASS }
   */
  void CHAVisitor::CalculateValidM(){
    // for each class
    for(auto i = ClassMultiSubclassMap.begin(), e1 = ClassMultiSubclassMap.end();
      i != e1;
      i++) {
      // find all virtual methods including original ones and inherited ones
      CXXRecordDecl * CRD = i->first;
      std::vector<std::string> VMethodsNames = this->FindAllVMethodString(CRD, false, false);
      // for all virtual methods including original ones and inherited ones
      for(std::string VMethodName : VMethodsNames){
        // 1)2) Original vmethods of subclasses and itself
        // for all of its subclasses
        // (including multiple-layer inherit, calculated by this->CalculateAllSubclass())
        for(CXXRecordDecl * SubclassCRD : i->second){
          // for all vmethods in the *SubclassCRD* with the name *VMethodName*
          std::vector<CXXMethodDecl *> VMethods = FindVMethodPointer(SubclassCRD, VMethodName);
          for(CXXMethodDecl * VMethod : VMethods){
            ValidM[CRD][VMethodName].insert(VMethod);
          }
        }
        // 3) vmethods inherited for CRD's base classes
        for(CXXMethodDecl * InheritedVMethod : ClassInheritedVMethodPtrMap[CRD]){
          if(this->GetFunctionAsString(InheritedVMethod, false, false) == VMethodName){
            ValidM[CRD][VMethodName].insert(InheritedVMethod);
          }
        }
      }
    }
  }

  // TODO:
  // void CHAVisitor::CalculateValidVT(){
  // }

  /*
   * Print CRD's class name
   */
  void CHAVisitor::PrintClass(CXXRecordDecl * CRD){
    llvm::outs() << "Inside VisitCXXRecordDecl: "
      << CRD->getQualifiedNameAsString() << '\n';
  }

  /*
   * Print all base classes of a give C++ class
   */
  void CHAVisitor::PrintBaseClass(CXXRecordDecl * CRD){
    for(auto i = CRD->bases_begin(),
      e = CRD->bases_end();
      i != e;
      i++) {
      CXXRecordDecl *BaseCRD = i->getType()->getAsCXXRecordDecl();
      llvm::outs() << "\tBase class: "
        << BaseCRD->getNameAsString() << '\n';
    }
  }

  /*
   * Print all virtual methods of a give C++ class
   */
  void CHAVisitor::PrintVirtualMethod(CXXRecordDecl * CRD){
    for(auto i = CRD->method_begin(),
      e = CRD->method_end();
      i != e;
      i++) {
      Decl *D = *i;
      if(CXXMethodDecl *CMD = dyn_cast<CXXMethodDecl>(D)){
        if(CMD->isVirtual())
          llvm::outs() << "\tVirtual Method: "
          << this->GetFunctionAsString(CMD, true, true) << '\n';
      }
    }
  }

  /*
   * Return a Function's as a string
   * Including FunctionName and parameter type
   * e.g. "m1(int,float)"
   */
  std::string CHAVisitor::GetFunctionAsString(CXXMethodDecl * CMD, bool Qualified, bool WithParams){
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

  /*
   * Construct *ClassSubclassMap*
   * VisitCXXRecordDecl only construct hierachy between two adjacent classes
   * We have to find ALL subclasses of a given class
   * Loop until calculated subclasses are fixed
   */
  void CHAVisitor::CalculateAllSubclass(){
    // copy ClassSubclassMap to ClassMultiSubclassMap
    for(auto i1 = ClassSubclassMap.begin(), e1 = ClassSubclassMap.end();
      i1 != e1;
      i1++){
      for(CXXRecordDecl * SubclassCRD : i1->second){
        ClassMultiSubclassMap[i1->first].insert(SubclassCRD);
      }
    }
    // loop until stable
    bool Changed;
    do {
      Changed = false;
      for(auto i = ClassMultiSubclassMap.begin(), e = ClassMultiSubclassMap.end();
        i != e;
        i++){
          // for a given class
          // insert its subclass's subclass into its subclass list
          for(CXXRecordDecl * SubclassCRD : i->second){
            for(CXXRecordDecl * SubsubclassCRD : ClassMultiSubclassMap[SubclassCRD]){
              // see if the class's subclass list contains Subsubclass
              if(i->second.find(SubsubclassCRD) == i->second.end()){
                // if the class's subclass list does not contain Subsubclass
                // Insert and mark 'Changed'
                i->second.insert(SubsubclassCRD);
                Changed = true;
              }
            }
          }
        }
    }while(Changed);
  }

  /*
   * Construct *ClassVMethodMap*
   * Store the name (unqualified) of
   * its own virutual methods and virutual methods inherited from its base class
   * into *ClassVMethodMap[Class]*
   */
  void CHAVisitor::CalculateInheritedVMethod(){
    bool Changed;
    do {
      Changed = false;
      for(auto i = ClassSubclassMap.begin(), e = ClassSubclassMap.end();
        i != e;
        i++){
          // for a given class
          // get its vmethods list including original and inherited ones
          // with unqualified name with parameters
          CXXRecordDecl * CRD = i->first;
          std::vector<CXXMethodDecl *> AllMethods = this->FindAllVMethodPointer(CRD);
          for(CXXRecordDecl * SubclassCRD : i->second){
            // for its subclass
            // check whether a vmethod is in original vmethod list or inherited vmethod list
            for(CXXMethodDecl * Method : AllMethods){
              std::string MethodStr = GetFunctionAsString(Method, false, true);
              if(ClassOriginalVMethodStrMap[SubclassCRD].find(MethodStr) ==
                ClassOriginalVMethodStrMap[SubclassCRD].end()){
                // SubclassCRD does not override Method
                if(ClassInheritedVMethodStrMap[SubclassCRD].find(MethodStr) ==
                  ClassInheritedVMethodStrMap[SubclassCRD].end()){
                  // insert method into inherited map
                  ClassInheritedVMethodPtrMap[SubclassCRD].insert(Method);
                  ClassInheritedVMethodStrMap[SubclassCRD].insert(MethodStr);
                  Changed = true;
                }else{
                  // already in inherited map
                }
              }
            }
          }
        }
    }while(Changed);
  }

  /*
   * return a list of unqualified names
   * of all virtual methods of a given C++ class *CRD*
   * including original ones and inherited ones
   */
  std::vector<std::string> CHAVisitor::FindAllVMethodString(CXXRecordDecl * CRD, bool Qualified, bool WithParams){
    std::vector<std::string> VMethods;
    // for all original methods
    for(auto i = ClassOriginalVMethodPtrMap[CRD].begin(), e = ClassOriginalVMethodPtrMap[CRD].end();
      i != e;
      i++){
      VMethods.push_back(this->GetFunctionAsString(*i, Qualified, WithParams));
    }
    // for all inherited methods
    for(auto i = ClassInheritedVMethodPtrMap[CRD].begin(), e = ClassInheritedVMethodPtrMap[CRD].end();
      i != e;
      i++){
      VMethods.push_back(this->GetFunctionAsString(*i, Qualified, WithParams));
    }
    return VMethods;
  }

  /*
   * return a list of pointers
   * to all virtual methods of a given C++ class *CRD*
   * including original ones and inherited ones
   */
  std::vector<CXXMethodDecl *> CHAVisitor::FindAllVMethodPointer(CXXRecordDecl * CRD){
    std::vector<CXXMethodDecl *> VMethods;
    // for all original methods
    for(auto i = ClassOriginalVMethodPtrMap[CRD].begin(), e = ClassOriginalVMethodPtrMap[CRD].end();
      i != e;
      i++){
      VMethods.push_back(*i);
    }
    // for all inherited methods
    for(auto i = ClassInheritedVMethodPtrMap[CRD].begin(), e = ClassInheritedVMethodPtrMap[CRD].end();
      i != e;
      i++){
      VMethods.push_back(*i);
    }
    return VMethods;
  }

  /*
   * return method pointers
   * to the origin virtual method of a given C++ class *CRD* with *MethodName* (e.g. m1)
   * [There may be more than one virtual methods with the same MethodName]
   */
  std::vector<CXXMethodDecl *> CHAVisitor::FindVMethodPointer(CXXRecordDecl * CRD, std::string MethodName){
    std::vector<CXXMethodDecl *> VMethods;
    // for all methods
    for(auto i = CRD->method_begin(),
      e = CRD->method_end();
      i != e;
      i++) {
      Decl *D = *i;
      if(CXXMethodDecl *CMD = dyn_cast<CXXMethodDecl>(D)){
        if(CMD->isVirtual() && CMD->getNameAsString() == MethodName)
          VMethods.push_back(CMD);
      }
    }
    return VMethods;
  }



  // AST Consumer
  class FindNamedClassConsumer : public clang::ASTConsumer {
    CompilerInstance &Instance;
    std::set<std::string> ParsedTemplates;
  public:
    FindNamedClassConsumer(CompilerInstance &Instance,
                         std::set<std::string> ParsedTemplates)
      : Instance(Instance), ParsedTemplates(ParsedTemplates) {}


    void HandleTranslationUnit(ASTContext& context) override {
      CHAVisitor v(ParsedTemplates, &context);
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
        llvm::errs() << "PrintFunctionNames arg = " << args[i] << "\n";

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

}

static FrontendPluginRegistry::Add<FindNamedClassAction>
X("ClassHierachyAnalysis", "ClassHierachyAnalysis");

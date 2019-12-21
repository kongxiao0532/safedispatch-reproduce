#include "stdio.h"


class A{
    public:
    virtual void m1(){
        printf("m1 with no arguments in A\n");
    }
    virtual void m1(int a){
        printf("m1 with int argument in A\n");
    }
    virtual void m2(){
        printf("m2 in A\n");
    }
    virtual void m3(){
        printf("m3 in A\n");
    }
    virtual void foo(){
        printf("foo in A\n");
    }
};

class B : public A{
    public:
    void m1(){
        printf("m1 with no arguments in B\n");
    }
    void m1(int a){
        printf("m1 with int argument in B\n");
    }
    void foo(){
        printf("foo in B\n");
    }
};

class C : public A{
    public:
    void m1(){
        printf("m1 in C\n");
    }
};

class D : public C{
    public:
    void m2(){
        printf("m2 in D\n");
    }
};

class E : public C{
    class AInsideE {
        private:
            int _123;
    };
    public:
    void m3(){
        printf("m3 in E\n");
    }
};



int main(){
    // class pointer
    A *testA;
    testA = new A();
    testA->m1();
    testA->m1(1);
    testA->m2();
    testA->m3();
    testA->foo();
    testA = new B();
    testA->m1();
    testA->m1(1);
    testA->m2();
    testA->m3();
    testA->foo();
    testA = new C();
    testA->m1();
    testA->m1(1);
    testA->m2();
    testA->m3();
    testA->foo();
    testA = new D();
    testA->m1();
    testA->m1(1);
    testA->m2();
    testA->m3();
    testA->foo();
    testA = new E();
    testA->m1();
    testA->m1(1);
    testA->m2();
    testA->m3();
    testA->foo();
    B * testB = new B();
    testB->m1();
    testB->m1(1);
    testB->m2();
    testB->m3();
    testB->foo();
    C * testC = new C();
    testC->m1();
    testC->m2();
    testC->m3();
    testC->foo();
    testC = new D();
    testC->m1();
    testC->m2();
    testC->m3();
    testC->foo();
    testC = new E();
    testC->m1();
    testC->m2();
    testC->m3();
    testC->foo();
    D * testD = new D();
    testD->m1();
    testD->m2();
    testD->m3();
    testD->foo();
    E * testE = new E();
    testE->m1();
    testE->m2();
    testE->m3();
    testE->foo();
    return 0;
}
// #include "stdio.h"


class A{
    public:
    virtual void m1(){
        // printf("m1 with no arguments in A");
    }
    virtual void m1(int a){
        // printf("m1 with int argument in A");
    }
    virtual void m2(){
        // printf("m2 in A");
    }
    virtual void m3(){
        // printf("m3 in A");
    }
    virtual void foo(){
        // printf("foo in A");
    }
};

class B : public A{
    public:
    void m1(){
        // printf("m1 with no arguments in B");
    }
    void m1(int a){
        // printf("m1 with int argument in B");
    }
    void foo(){
        // printf("foo in B");
    }
};

class C : public A{
    public:
    void m1(){
        // printf("m1 in C");
    }
};

class D : public C{
    public:
    void m2(){
        // printf("m2 in D");
    }
};

class E : public C{
    class AInsideE {
        private:
            int _123;
    };
    public:
    void m3(){
        // printf("m3 in E");
    }
};



int main(){
    // class pointer
    A *testA;
    testA = new A();
    testA->m3();
    testA = new C();
    testA->m3();
    testA = new E();
    testA->m3();
    // function pointer
    void (A::*f) (void);
    f = &A::foo;
    testA = new A();
    (testA->*f)();
    testA = new B();
    (testA->*f)();
    
    A a;
    B b;
    C c;
    D d;
    E e;
    a.m1();
    a.m2();
    a.m3();
    b.m1();
    b.m2();
    b.m3();
    c.m1();
    c.m2();
    c.m3();
    d.m1();
    d.m2();
    d.m3();
    e.m1();
    e.m2();
    e.m3();
    return 0;
}
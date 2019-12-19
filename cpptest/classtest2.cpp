#include "stdio.h"


class A{
    public:
    virtual int m1(){
        return 0;
        // printf("m1 in A");
    }
    virtual int m2(){
        return 1;
        // printf("m2 in A");
    }
    void m3(){
        // printf("m3 in A");
    }
};

class B : public A{
    public:
    virtual int m2(){
        return 2;
        // printf("m1 in B");
    }
};


int main(){
    // class pointer
    A *testA;
    testA = new A();
    B *testB = new B();
    testA->m1();
    testA = new B();
    testA->m1();
    testB->m1();
    testA->m2();
    testB->m2();
    return 0;
}
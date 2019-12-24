#include <cstdint>
#include<cstdio>
#include<cstring>
void activatesth();



class ckx
{

public:
    int data[1000];
    int nameid = 1000;
    virtual void dosth1();
    virtual void dosth2();
};

void ckx::dosth1(){

    printf("this is ckx dosth1\n");
}

void ckx::dosth2()
{

    printf("this is ckx dosth2\n");
}

class base
{
public:
    int k = 0000;
    virtual void double_the_size();
    virtual void printthis();
    void changevptr();
    // ckx: 当base为abstract class的时候 autocoop还不能hold这种情况
};
void base::printthis(){
    void**vptr=(void**)this;
    printf("obj start at %p\n",this);
    printf("vptr is %p\n",*vptr);
}
void base::changevptr(){
    printf("change vptr to:");

    scanf("%p",this);
    void **vptr = (void **)this;
    printf("vptr is %p\n", *vptr);
}


class D2 : public base
{
    ckx *ptr;
    uint64_t area;

public:
    uint64_t length;
    uint64_t width;
    virtual void double_the_size(); //{
    //     length*=2;
    //     width*=2;
    //   }
};
void base::double_the_size()
{
    ;
}

void D2::double_the_size()
{
    printf("D2-func\n");
    int nid;
    ptr = new ckx();
    nid = ptr->nameid;
    length *= 2;
    width *= 2;
}

class D3 : public D2
{
public:
    uint64_t volume;
    uint64_t height;
    virtual void double_the_size();
    virtual void count_volume()
    {
        
        volume = length * width * height;
    }
};
void D3::double_the_size()
{
    printf("D3-func\n");
    k = k + 1;
    length *= 2;
    width *= 2;
    height *= 2;
}

base *obj; //global pointer
base *obj2;

void callback(base *obj)
{

    obj->double_the_size();
};
void activatesth(){
    obj2=new D3;
    callback(obj2);
    ckx* ptr = new ckx;
    ptr->dosth1();
    ptr->dosth2();
    
}



void trigger(){

    callback(obj);
    
}



int main()
{
    // obj = new base;

    activatesth();

    obj = new D3;
    obj->printthis();



    obj = new D2;
    // obj->this;
    // void **vptr = new D2;




    obj->printthis();
    obj->changevptr();

    // printf("obj address is %p\n",obj);
    // printf("obj address is %p\n", *vptr);

    // printf("vptr address is 0x%lx\n",*obj);

    




    trigger();
    // callback(obj);
    // activatesth();
}


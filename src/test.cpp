//
// Created by x on 2020/5/9.
//

//
// Created by x on 2020/4/21.
//
#include <iostream>

class Base1{
public:
    int i=1;
    char c1='1';
    char c2='2';
    virtual void vfun(){
        std::cout << "vfun1" << std::endl;
    }
};
class Base2{
public:
    int i=2;
    char c1='3';
    char c2='4';
    virtual void vfun(){
        std::cout << "vfun2" << std::endl;
    }
    void work(){}
};
class Derived: public Base1, public Base2{
public:
    int i = 3;
    char c1='5';
    char c2='6';
    virtual void vfun(){
        std::cout << "vfun3" << std::endl;
    }
};

long* mem_fun_slot(void* object, int index){
    long* vptr = (long*)*(long*)object;
    return vptr + index;
}
int main(){
    Derived d;
    using BaseType = Base2;

    BaseType& b = dynamic_cast<BaseType&>(d);
    std::cout << &b << " " << &d << std::endl;//地址有差异

    typedef void(*base_fun)(BaseType*);
    base_fun vf1 = (base_fun)*mem_fun_slot(&b, 0);
    vf1(&b);

    long* slot1 = mem_fun_slot(&b, 0);
//    *slot1 = 0;// 段错误，　因为表位于只读内存段

    *(long*)(&d) = *(long*)(&b);
    d.vfun();
}
//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <boost/pool/object_pool.hpp>

class Obj {
    int a;
    int b;
    std::string str;
};

TEST(HFT, MEMORY_OBJECT_POOL) {
    boost::object_pool<Obj> alloc;
    for (int i = 0; i < 10000; ++i) {
        void *mem = alloc.malloc();
// 注意；X的构造函数不会被调用，仅仅是分配大小为sizeof(Obj)的内存块。
// 如果需要调用构造函数（像new一样），应该调用construct。
        Obj *obj1 = new(mem) Obj();
// 调用了placement new，从而得到真正意义上的Obj类型的对象。

        Obj *obj2 = alloc.construct();
        alloc.destroy(obj2);

// 你可以忘记释放obj1，boost::object_pool会记得这件事情。
    }
}
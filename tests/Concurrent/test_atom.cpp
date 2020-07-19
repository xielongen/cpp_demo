//
// Created by x on 2020/4/18.
//

///////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

void unorder(int n) {
    int a = 0;
    int b = 100;
    int flag = 0;

    std::thread t1([&]() {
        while (flag != 1);
        if (a + b != 100) {
            std::cout << a << " " << b << " " << a + b << std::endl;
            exit(0);
        }
    });
    auto switch_fn = [&](int i) {
        a = i;
        b = 100 - i;
        flag = 1;
    };
    std::thread t2(switch_fn, n);

    t1.join();
    t2.join();
}

TEST(CXX, UNORDER) {
    for (int i = 0; i < 10000000; i++) {
        unorder(i);
    }
}
////////////////////////////////////////////////////////////
#include <atomic>

struct A {
    float x;
    int y;
    long long z;
};
std::atomic<int> count = {0};

#include <util.h>

TEST(CXX, ATOM) {
    std::atomic<A> a;
    std::atomic<int> int_num;
    std::cout << std::boolalpha << a.is_lock_free() << int_num.is_lock_free() << std::endl;

    std::thread t1([]() {
        count.fetch_add(1);
    });
    std::thread t2([]() {
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();

    std::cout << count << std::endl;
}
/////////////////////////////////////////////////////////
TEST(CXX, WAIT) {
    std::atomic<int *> ptr;
    int v;
    std::thread producer([&]() {
        int *p = new int(42);
        v = 1024;
        ptr.store(p, std::memory_order_release);
    });
    std::thread consumer([&]() {
        int *p;
        while (!(p = ptr.load(std::memory_order_consume)));

        std::cout << "p: " << *p << std::endl;
        std::cout << "v: " << v << std::endl;
    });
    producer.join();
    consumer.join();
}
//TEST(ATOM. PERF{
//    std::atomic<int> flag;
//    flag.load()
//}
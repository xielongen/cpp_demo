//
// Created by x on 19-11-30.
//

#include <gtest/gtest.h>
#include <util.h>

int sum(int a, int b, int c){
    return a + b;
}

TEST(HFT, COUMPUTE) {
    int a, b = 1000, c = 10000;
    auto start = rdtsc();

    volatile int d;
    for (int i = 0; i < 1000; i++) {
//        rdtsc();
        a = sum(b, c, d);
    }
    auto end = rdtsc();

    std::cout << std::endl << "TimeCost:" << end - start << std::endl;
}

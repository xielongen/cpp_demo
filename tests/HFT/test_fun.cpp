//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <util.h>

int fun(int a, int b){
    return a + b;
}

TEST(FUN, function){
    auto test_data = range(0, 10000, 1);
    auto start = rdtsc();
//    for(auto i: test_data){
//        fun(i, 100);
//    }
    for(int i = 0; i < 10000; i++){
        fun(i, 100);
    }
    auto end = rdtsc();
    std::cout << end - start << std::endl;
}
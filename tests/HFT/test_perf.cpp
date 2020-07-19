//
// Created by x on 2020/4/13.
//
#include <gtest/gtest.h>
#include <util.h>
#include <atomic>
#include <mutex>

std::atomic<int> perf_counter = {0};
TEST(PERF, ATOM) {
    auto s = rdtsc();
    perf_counter += 1;
    auto e = rdtsc();
    std::cout << e - s << std::endl;
}

std::mutex mu;
void lock() {
    std::unique_lock<std::mutex> lock(mu);
}
TEST(PERF, mutex){
    auto s = rdtsc();
    lock();
    auto e = rdtsc();
    std::cout << e - s << std::endl;
}
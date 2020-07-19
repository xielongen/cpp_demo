//
// Created by x on 19-12-5.
//
#include <util.h>
#include <assert.h>

std::vector<int> range(int start, int end, int step){
    std::vector<int> numbers;
    if(end > start){
        assert(step > 0);
        for(int i = start; i < end; i+=step){
            numbers.push_back(i);
        }
    }
    else{
        assert(step < 0);
        for(int i = start; i > end; i+=step){
            numbers.push_back(i);
        }
    }
    return numbers;
}

uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__
    (
    "rdtsc":"=a"(lo), "=d"(hi)
    );
    return (uint64_t) hi << 32 | lo;
}

int64_t now(){
    struct timeval val={0,0};
    gettimeofday(&val, NULL);
    return val.tv_sec * 1000000 + val.tv_usec;
}
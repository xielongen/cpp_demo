//
// Created by x on 19-12-5.
//

#ifndef CSAPP_UTIL_H
#define CSAPP_UTIL_H

#include <cstdint>
#include <vector>
#include <sys/time.h>

uint64_t rdtsc();

std::vector<int> range(int start, int end, int step);


#pragma pack(1)
struct TimeMessage {
    int64_t send_t;
    int64_t recv_t;
};
#pragma pack(pop)
static_assert(sizeof(TimeMessage) == 16, "Messsage size should be 16");

int64_t now();

#endif //CSAPP_UTIL_H

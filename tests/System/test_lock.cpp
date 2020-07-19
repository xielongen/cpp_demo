//
// Created by x on 19-12-5.
//
#include<gtest/gtest.h>

///////////////////////////////////////////////////////////////
TEST(LOCK, MUTEX){
    pthread_mutex_t mutex;

    auto res = pthread_mutex_init(&mutex, NULL);
    if(res != 0)
    {
        perror("pthread_mutex_init failed\n");
        exit(EXIT_FAILURE);
    }

    long MAX = 1000000000;
    long c = 0;

    while(c < MAX)
    {
        pthread_mutex_lock(&mutex);
        c = c + 1;
        pthread_mutex_unlock(&mutex);
    }
}

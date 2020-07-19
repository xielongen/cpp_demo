//
// Created by x on 20-1-25.
//

#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex;
queue<int> product;

void * produce(void *ptr)
{
    for (int i = 0; i < 10; ++i)
    {
        pthread_mutex_lock(&mutex);
        product.push(i);
        pthread_mutex_unlock(&mutex);
    }
}

void * consume(void *ptr)
{
    for (int i = 0; i < 10;)
    {
        pthread_mutex_lock(&mutex);

        if (product.empty())
        {
            pthread_mutex_unlock(&mutex);
            continue;
        }

        ++i;
        cout<<"consume:"<<product.front()<<endl;
        product.pop();
        pthread_mutex_unlock(&mutex);
    }
}

TEST(LOCK, ConsumerProduct){

    pthread_mutex_init(&mutex, NULL);

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, consume, NULL);
    pthread_create(&tid2, NULL, produce, NULL);

    void *retVal;

    pthread_join(tid1, &retVal);
    pthread_join(tid2, &retVal);
}
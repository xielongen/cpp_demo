//
// Created by x on 2020/4/18.
//

#include <gtest/gtest.h>
#include <thread>
#include <iostream>
#include <future>

class ThreadGuard{
    std::thread& thread;
public:
    explicit ThreadGuard(std::thread& t):thread(thread){}
    ~ThreadGuard(){
        if(thread.joinable()){
            thread.join();
        }
    }
    ThreadGuard(ThreadGuard const &)=delete;
    ThreadGuard& operator=(ThreadGuard const &)=delete;
};
int acc;
TEST(THREAD, JOIN){
    struct RefCall{
        int& acc;
        RefCall(int& acc):acc(acc){}
        void operator()(){
            std::cout << "Thread Start" << std::endl;
            for(int i=0; i < 100000000; i++){
                acc += 1;
            }
            std::cout << "Thread Finished" << std::endl;
        }
    };
    auto fun = RefCall(acc);
    std::thread t(fun);
    ThreadGuard tg(t);
//    t.join();
    std::cout << acc << std::endl;
}

void do_work(unsigned id){
    std::cout << "Thread " << id << "is working!" << std::endl;
}

TEST(THREAD, BATCH){
    std::cout << "Core Num:" << std::thread::hardware_concurrency() << std::endl;
    std::vector<std::thread> threads;
    for(unsigned i=0; i < 3; ++i)
    {
        threads.push_back(std::thread(do_work,i)); // 产生线程
    }
    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));
}
#include <math.h>

double complex_compute(){
    double res = 0;
    for(long i=1; i < 3000000000; i++){
        res += (1.0 / i / i);
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return sqrt(res * 6);
}
std::string now(){
    auto end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::string(std::ctime(&end_time));
};
TEST(THREAD, FUTURE){
    std::cout << now() << " Wait answer " << std::endl;
    auto answer = std::async(complex_compute);
    auto res = answer.get();
    std::cout << now() << " The answer is " << res << std::endl;
}
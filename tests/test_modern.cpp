//
// Created by x on 19-11-29.
//
#include <gtest/gtest.h>
#include <regex>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <variant>

/////////////////////////////////////////////////////////////////////
std::tuple<int, int, int> f(int i) {
    return std::make_tuple(i, i * i, i * i * i);
}

int test(int a, int b, int c) {
    return a + b + c;
}

TEST(CXX, BASIC) {
    std::vector<int> vec = {1, 2, 3, 4};
    auto tup = std::make_tuple(1, 2, 3, 4);
    auto[a, b, c] = f(100);
    std::cout << a << b << c << std::endl;
//    auto [a, b, c] = f();
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);itr != vec.end()) {
        *itr = 4;
    }
    auto bf = std::bind(test, std::placeholders::_1, 3, 4);
    std::cout << bf(10) << std::endl;
}
//////////////////////////////////////////////////////////////////
// pack
using std::string;

void append(std::string &s) {
    s += "!!!!";
}

TEST(CXX, MOVE) {
    std::string s = "abcd";
    std::string &&rs = std::move(s);
    append(rs);
    std::cout << s << std::endl;

    const std::string &s2 = std::move(s);
}

//////////////////////////////////////////////////////////////////
void reference(int &v) {
    std::cout << "左值" << std::endl;
}

void reference(int &&v) {
    std::cout << "右值" << std::endl;
}

template<typename T>
void pass(T &&v) {
    std::cout << "普通传参:";
    reference(v); // 始终调用 reference(int&)
}

TEST(CXX, FORWARD) {
    std::cout << "传递右值:" << std::endl;
    pass(1); // 1是右值, 但输出是左值

    std::cout << "传递左值:" << std::endl;
    int l = 1;
    pass(l); // l 是左值, 输出左值
}

/////////////////////////////////////////////////////////////////////
// var template args
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}

TEST(CXX, VAR_TEMP_ARGS) {
    printf2(1, "fdsfd", 4.3);
}

/////////////////////////////////////////////////////////////////////
std::tuple<int, std::string> nextToken() {
    return {4, "fallthrough"};
}

TEST(CXX, TUPLE) {
    auto token = nextToken();
    std::cout << std::get<int>(token) << "," << std::get<std::string>(token);

    auto[tokenType, lexeme] = nextToken();
    std::cout << tokenType << "," << lexeme;
}
//////////////////////////////////////////////////////////////////
TEST(CXX, ANYONE) {
    static auto anyone = [](auto &&k, auto &&... args) -> bool { return ((args == k) || ...); };
    char x = 'e';
    if (anyone(x, 'x', 'X', 'e', 'E', '.')) {
        std::cout << "Match" << std::endl;
    }
}

//////////////////////////////////////////////////////////////////
TEST(CXX, REGEX) {
    std::string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    // 在 C++ 中 \ 会被作为字符串内的转义符，为使 \. 作为正则表达式传递进去生效，需要对 \ 进行二次转义，从而有 \\.
    std::regex txt_regex("[a-z]+\\.txt");
    for (const auto &fname: fnames)
        std::cout << std::boolalpha << fname << ": " <<
                  std::regex_match(fname, txt_regex) << std::endl;

    std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;
    for (const auto &fname: fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // std::smatch 的第一个元素匹配整个字符串
            // std::smatch 的第二个元素匹配了第一个括号表达式
            if (base_match.size() == 2) {
                std::string base = base_match[1].str();
                std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
                std::cout << fname << " sub-match[1]: " << base << std::endl;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////
std::mutex mtx;
int counter = 0;

void increase() {
    std::unique_lock<std::mutex> lock(mtx);
    counter += 1;
}

#include <thread>

TEST(CXX, THREAD) {
    for (int i = 0; i < 10; i++) {
        std::thread t(increase);
        t.join();
    }
    std::cout << counter << std::endl;
}

#include <future>

TEST(CXX, FUTURE) {
    std::packaged_task<int()> task([]() { return 7; });
    // 获得 task 的期物
    std::future<int> result = task.get_future(); // 在一个线程中执行 task
    std::thread(std::move(task)).detach();
    std::cout << "waiting...";
    result.wait(); // 在此设置屏障，阻塞到期物的完成
    // 输出执行结果
    std::cout << "done!" << std::endl << "future result is " << result.get() << std::endl;
}

#include <condition_variable>
#include <queue>

TEST(CXX, CONDITION) {
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;  // 通知信号

    // 生产者
    auto producer = [&]() {
        for (int i = 0;; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all(); // 此处也可以使用 notify_one
        }
    };
    // 消费者
    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified) {  // 避免虚假唤醒
                cv.wait(lock);
            }
            // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 消费者慢于生产者
            lock.lock();
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    // 分别在不同的线程中运行
    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i) {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
}

TEST(CXX, TIME) {
    using namespace std::chrono;
    system_clock::time_point tp_epoch;    // epoch value
    time_point<system_clock, duration<int>> tp_seconds(duration<int>(1));
    system_clock::time_point tp(tp_seconds);
    std::cout << "1 second since system_clock epoch = ";
    std::cout << tp.time_since_epoch().count();
    std::cout << " system_clock periods." << std::endl;
    // display time_point:
    std::time_t tt = system_clock::to_time_t(tp);
    std::cout << "time_point tp is: " << ctime(&tt);
}

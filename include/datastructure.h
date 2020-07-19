//
// Created by x on 2020/4/20.
//

#ifndef CSAPP_DATASTRUCTURE_H
#define CSAPP_DATASTRUCTURE_H

#include <exception>
#include <stack>
#include <memory>
#include <mutex>

struct EmptyStackException: std::exception{
    const char* what() const throw(){
        return "Empty Stack";
    }
};

template<typename T> class ThreadSafeStack{
    std::stack<T> data;
    std::mutex mt;
public:
    ThreadSafeStack():data(std::stack<T>()){};
    ThreadSafeStack(const ThreadSafeStack& other){
        std::lock_guard<std::mutex>(other.mt);
        data = other.data
    }
    ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;

    void push(T new_value){
        std::lock_guard<std::mutex>(mt);
        data.push(new_value);
    };
    std::shared_ptr<T> pop(){
        std::lock_guard<std::mutex>(mt);
        if(data.empty()){
            throw EmptyStackException();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T& value){
        std::lock_guard<std::mutex>(mt);
        if(data.empty()){
            throw EmptyStackException();
        }
        value = data.pop();
        data.pop();
    }
    bool empty() const{
        std::lock_guard<T>()
    }
};
#endif //CSAPP_DATASTRUCTURE_H

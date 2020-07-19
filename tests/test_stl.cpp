//
// Created by x on 2020/4/18.
//

#include <gtest/gtest.h>
#include <stack>

struct empty_stack: std::exception
{
    const char* what() const throw();
};

TEST(STL, STACK){
    std::stack<int> stack;
    std::vector<int> result;
    stack.push(100);
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    std::for_each(result.begin(), result.end(), [](int i){
        std::cout << i << std::endl;
    });
}
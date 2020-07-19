//
// Created by x on 19-12-3.
//
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

enum class open_modes { input, output, append };
class Base{

};

class Derived : Base {
public:
    using Base::Base;
    /* ... */
};

TEST(BASIC, LANGUAGE){
    std::initializer_list<int> args = {1,2,3};
    auto number = {1,2,3,4,5};
    std::for_each(number.begin(), number.end(), [](auto i){std::cout << i << std::endl;});
}
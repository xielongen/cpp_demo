//
// Created by x on 19-12-5.
//
#include<gtest/gtest.h>
#include <string>
#include <iostream>
#include <vector>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>

TEST(BOOST, FOREACH) {
    std::string test("Hello, world!");  // string 可以视为 char 的容器
    BOOST_FOREACH(char ch, test) {
                    std::cout << ch << std::endl;
                }
}

TEST(BOOST, LAMBDA){

    boost::function<int(const char*)> f = atoi;
    std::cout << f("42") << '\n';

    f = strlen;
    std::cout << f("42") << '\n';
    std::vector<int> v;

    // 此处填充 v
    for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");
}


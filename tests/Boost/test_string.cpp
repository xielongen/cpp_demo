//
// Created by x on 19-11-23.
//
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lambda/lambda.hpp>
using namespace boost::lambda;

TEST(BOOST, STRINIG) {
    std::vector<std::string> v = {"A", "B", "C", "D"};
    std::cout << boost::algorithm::join(v, " ") << '\n';
}

#include <boost/format.hpp>
TEST(BOOST, FORMAT){
    using std::cout;
    using boost::format;
    cout << format("%1% %2% %3% %2% %1%") % "11" % "22" % "333";
    cout << format("%s  %d") % "price" % 1234;
}

#include <boost/lexical_cast.hpp>
TEST(BOOST, CONV){
    std::string s = "100";
    int a = boost::lexical_cast<int>(s);
    int b = 1;
    std::cout << std::endl;
    std::cout << (a + b) << std::endl;//输出101

    std::string ss = boost::lexical_cast<std::string>(123);
    std::cout << ss << '\n';

    double d = boost::lexical_cast<double>(ss);
    std::cout << d << '\n';
}

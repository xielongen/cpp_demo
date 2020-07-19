//
// Created by x on 19-12-11.
//

#include <range/v3/all.hpp>
#include <gtest/gtest.h>
#include <util.h>

using std::cout ;
TEST(EASY, FOREACH){
    std::string s{"hello"};
    ranges::for_each(s, [](char c) { cout << c << ' '; });
    cout << '\n';
}

#include <range/v3/view/all.hpp>
using std::cout;
auto is_six = [](int i) { return i == 6; };

TEST(EASY, LOGICAL){
    std::vector<int> v{6, 2, 3, 4, 5, 6};
    cout << std::boolalpha;
    cout << "vector: " << ranges::views::all(v) << '\n';
    cout << "vector any_of is_six: " << ranges::any_of(v, is_six) << '\n';
    cout << "vector all_of is_six: " << ranges::all_of(v, is_six) << '\n';
    cout << "vector none_of is_six: " << ranges::none_of(v, is_six) << '\n';
}

TEST(EASY, COUNT)
{
    std::vector<int> v{6, 2, 3, 4, 5, 6};
    // note the count return is a numeric type
    // like int or long -- auto below make sure
    // it matches the implementation
    auto c = ranges::count(v, 6);
    cout << "vector:   " << c << '\n';
    std::array<int, 6> a{6, 2, 3, 4, 5, 6};
    c = ranges::count(a, 6);
    cout << "array:    " << c << '\n';
}
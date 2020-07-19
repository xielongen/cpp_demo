//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <boost/circular_buffer.hpp>
#include <boost/multi_array.hpp>

TEST(BOOST, MULTI_ARRAY) {
    typedef boost::multi_array<double, 3> array_type;
    typedef array_type::index index;
    array_type A(boost::extents[3][4][2]);

    int values = 0;
    for (index i = 0; i != 3; ++i)
        for (index j = 0; j != 4; ++j)
            for (index k = 0; k != 2; ++k)
                A[i][j][k] = values++;
}

TEST(BOOST, CIRCLAR) {
    boost::circular_buffer<int> cb(3);  // Create with capacity for 3 integers
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

// The buffer is full now
// pushing subsequent elements will overwrite front-most elements.

    cb.push_back(4);  // Overwrite 1 with 4.
    cb.push_back(5);  // Overwrite 2 with 5.
// The buffer now contains 3, 4 and 5.

// Elements can be popped from either the front or the back.
//    cb.pop_back();  // 5 is removed.
//    cb.pop_front(); // 3 is removed.

    for (auto &i: cb) {
        std::cout << i << std::endl;
    }
}
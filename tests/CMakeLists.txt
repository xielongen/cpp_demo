cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
find_package(glog 0.4.0 REQUIRED)
find_package(OpenMP)

find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(../src/)
include_directories(../include/)

file(GLOB SRCS
        *.cpp
        Boost/*.cpp
        Easy/*.cpp
        HFT/*.cpp
        Network/*.cpp
        System/*.cpp
        Concurrent/*.cpp
        )
list(REMOVE_ITEM SRCS HFT/test_lockfree.cpp)
foreach (file IN LISTS SRCS)
    message(STATUS ${file})
endforeach (file)


add_executable(TESTS ${SRCS})
target_link_libraries(TESTS util boost_system boost_thread boost_atomic ${GTEST_BOTH_LIBRARIES} glog::glog OpenMP::OpenMP_CXX atomic pthread)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(csapp)

include_directories(./include)
add_executable(Server src/network/server.cpp)
add_executable(Client  src/network/client.cpp)
add_executable(Main src/main.cpp src/test_python.cpp include/util.h src/util.cpp)
add_executable(Test src/test.cpp)
target_link_libraries(Main pthread)
add_library(util src/util.cpp)

enable_testing()
add_subdirectory(tests)

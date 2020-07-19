//
// Created by x on 19-11-23.
//
#include <gtest/gtest.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

TEST(IPC, PIP){
    int pipes[2];
    pipe(pipes);
    write(pipes[1], "hello", 5);

    char bufffer[1024];
    read(pipes[0], bufffer, 100);
    std::cout << bufffer << std::endl;
}
TEST(IPC, SOCK_PAIR){
    int fds[2];
    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
    assert(ret == 0);

    char* message = "Hello sock";
    write(fds[0], message, strlen(message));

    char read_buf[100];
    int read_count = read(fds[1], read_buf, strlen(message));
    read_buf[read_count] = '\0';
    std::cout << read_count << ", " << read_buf << std::endl;
}
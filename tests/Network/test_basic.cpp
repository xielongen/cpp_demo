//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>

TEST(NET, ORDER) {
    union {
        short value;
        char bytes[2];
    } test;
    test.value = 0x0201;
    if(test.bytes[0] == 1 && test.bytes[1] == 2){
        std::cout << "Small Endian" << std::endl;
    } else{
        std::cout << "Big Endian" << std::endl;
    }
}
TEST(NET, HTON){
    int address = 0x01020304;
    std::cout << sizeof(short) << " " << sizeof(unsigned int) << " " << sizeof(long) << std::endl;
    unsigned int net = htonl(address);
    std::cout << std::hex << net << std::endl;
}
TEST(NET, NAME){
    struct hostent* host =  gethostbyname("www.baidu.com");
    std::cout << host->h_name << std::endl;
    auto serv = getservbyname("www", "tcp");
    std::cout << ntohs(serv->s_port) << std::endl;

    struct addrinfo hints;
    struct addrinfo* res;
    bzero(&hints, sizeof(hints));
    getaddrinfo("www.baidu.com", "www", &hints, &res);
    freeaddrinfo(res);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(80);

    char host_str[100];
    char serv_str[100];
    getnameinfo((sockaddr*)&server_addr, sizeof(sockaddr), host_str, 100, serv_str, 100, 0);
    std::cout << host_str << serv_str << std::endl;
}
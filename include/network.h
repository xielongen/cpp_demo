//
// Created by x on 2020/4/19.
//

#ifndef CSAPP_NETWORK_H
#define CSAPP_NETWORK_H
#include <string>
#include <iostream>
#include <stdexcept>

#include <string.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <thread>
#include <map>

class Sock{
public:
    template<typename T> void zero(T& object){
        bzero(&object, sizeof(T));
    }
    void zero(char* buffer, size_t size){
        bzero(buffer, size);
    }
};

class Actor:public Sock{
public:
    int sock_fd;
    Actor():sock_fd(-1){};
    Actor(int sock_fd):sock_fd(sock_fd){};
    Actor(Actor&& actor):sock_fd(actor.sock_fd){
        actor.sock_fd = -1;
    }
    ~Actor(){
        if(sock_fd >= 0)
            close(sock_fd);
    }

    template<typename T> ssize_t Write(T& object){
        return send(sock_fd, &object, sizeof(object), 0);
    }
    template<typename T> ssize_t Read(T& object){
        return recv(sock_fd, &object, sizeof(object), 0);
    }
    ssize_t Write(const char* buffer){
        return send(sock_fd, buffer, strlen(buffer), 0);
    }
    ssize_t Write(char* buffer, size_t size){
        return send(sock_fd, buffer, size, 0);
    }
    ssize_t Read(char* buffer, size_t size){
        return recv(sock_fd, buffer, size, 0);
    }
};
class TcpClient: public Actor
{
    struct sockaddr_in server_addr;
public:
    TcpClient(std::string ip, int port)
    {
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = ntohs(port);
        inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
    }
    bool Connect()
    {
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(sock_fd, (sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            std::cout << "连接失败" << std::endl;
            return false;
        }
        return true;
    }
};

template<class T> class TcpServer: public Sock{
    struct sockaddr_in addr;
    int sock_fd;
public:
    TcpServer(int port, std::string ip, int serve_capacity=10) {
        sock_fd = socket(PF_INET, SOCK_STREAM, 0);
        if(sock_fd < 0){
            throw std::runtime_error("Create Sock fd error when create sock: " + ip + ":"  +std::to_string(port));
        }

        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = ntohs(port);
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

        int res = bind(sock_fd, (const sockaddr *) &addr, sizeof(addr));
        if(res == -1){
            throw std::runtime_error("Bind fd error when bind to address: " + ip + ":"  +std::to_string(port));
        }
        res = listen(sock_fd, serve_capacity);
        if(res == -1){
            throw std::runtime_error("listen fd error when listen to address: " + ip + ":"  +std::to_string(port));
        }
    }
    ~TcpServer(){
        close(sock_fd);
    }
    void run(){
        while(true){
            struct sockaddr_in client_addr;
            socklen_t client_size = sizeof(client_addr);
            int client_fd = accept(sock_fd, (sockaddr*)&client_addr, &client_size);
            if(client_fd < 0) {
                std::string error_message(strerror(errno));
                throw std::runtime_error("accept client_fd < 0: " + error_message);
            }

            std::cout << "客户端 IP: " << inet_ntoa(client_addr.sin_addr) <<
            ",  端口：" << ntohs(client_addr.sin_port)
            << " fd: " << client_fd << std::endl;

            T client(client_fd);
            std::thread t(std::move(client));
            t.detach();
        }
    }

};

class UdpClient{
protected:
    sockaddr_in server_addr;
    int sock_fd;
public:
    UdpClient(std::string ip, int port){
        memset(&server_addr, 0, sizeof(sockaddr_in));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = ntohs(port);
        inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

        sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sock_fd < 0){
            throw std::runtime_error("Create Sock fd error when create sock: " + ip + ":"  +std::to_string(port));
        }
    }
    ~UdpClient(){
        if(sock_fd >= 0)
            close(sock_fd);
    }
    template<typename T>ssize_t Write(T& object){
        sendto(sock_fd, &object, sizeof(object), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }
    ssize_t Write(char* buffer, ssize_t size){
        sendto(sock_fd, buffer, size, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }
    ssize_t Write(const char* message){
        sendto(sock_fd, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }

    template<typename T>ssize_t Read(T& object){
        socklen_t addr_len = 0;
        return recvfrom(sock_fd, &object, sizeof(object), 0, (struct sockaddr*)&server_addr, &addr_len);
    }
    ssize_t Read(char* buffer, ssize_t size){
        socklen_t addr_len = 0;
        return recvfrom(sock_fd, buffer, size, 0, (struct sockaddr*)&server_addr, &addr_len);
    }
};

template<class T>class UdpServer{
    struct sockaddr_in addr;
    int sock_fd;
public:
    UdpServer(int port, std::string ip) {
        sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sock_fd < 0){
            throw std::runtime_error("Create Sock fd error when create sock: " + ip + ":"  +std::to_string(port));
        }

        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = ntohs(port);
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

        int res = bind(sock_fd, (const sockaddr *) &addr, sizeof(addr));
        if(res == -1){
            throw std::runtime_error("Bind fd error when bind to address: " + ip + ":"  +std::to_string(port));
        }
    }
    ~UdpServer(){
        close(sock_fd);
    }
    void run(){
        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(sockaddr_in));
        client_addr.sin_family = AF_INET;

        socklen_t addr_len = sizeof(sockaddr_in);
        const int buffer_size = 1024 * 1024;
        char* buffer = new char[buffer_size];

        T server;
        while (true){
            ssize_t count = recvfrom(sock_fd, buffer, buffer_size, 0, (sockaddr*)&client_addr, &addr_len);
            if(count <= 0){
                std::cout << sock_fd <<
                " count: " << count <<
                " buffer: " << buffer <<
                " buffer_size: " << buffer_size <<
                " error: " << strerror(errno)
                << std::endl;
                exit(0);
            }
            if(server(buffer, &count, client_addr.sin_addr.s_addr, client_addr.sin_port))
                sendto(sock_fd, buffer, count, 0, (sockaddr*)&client_addr, addr_len);
        }
    }
};
#endif //CSAPP_NETWORK_H

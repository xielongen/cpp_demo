//
// Created by x on 2020/4/6.
//

//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/fcntl.h>

TEST(NET, WRITEV) {
    const char* ip = "0.0.0.0";
    int port = 10080;

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    server_addr.sin_port = ntohs(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int res = bind(sock, (sockaddr*)& server_addr, sizeof(server_addr));
    assert(res != -1);
    res = listen(sock, 5);
    assert(res != -1);

    struct sockaddr_in client;
    socklen_t client_addr_len = sizeof(client);
    std::cout << "Start to Accept" << std::endl;
    int clientfd = accept(sock, (sockaddr*) &client, &client_addr_len);
    assert(clientfd >= 0);
    std::cout << "客户端 IP: " << inet_ntoa(client.sin_addr) << ",  端口：" << ntohs(client.sin_port) << std::endl;

    const int head_size = 1000;
    char header_buf[head_size];
    memset(header_buf, '\0', head_size);

    char* path = "/tmp/test.csv";
    struct stat file_stat;
    stat(path, &file_stat);
    int file_size = file_stat.st_size;

    int fd = open(path, O_RDONLY);
    char* file_buf = new char[file_size + 1];
    memset(file_buf, '\0', file_size);
    read(fd, file_buf, file_size);

    char* stat_line[2] = {
            "200 OK",
            "500 Internal server error",
    };
    int len = 0;
    int left = head_size - 1;
    res = snprintf(header_buf + len, left, "%s %s\r\n",
            "HTTP/1.1", stat_line[0]);
    len += res;
    left -= res;

    res = snprintf(header_buf + len, left,"Content-Length: %d\r\n", file_size);
    len += res;
    left -= res;

    res = snprintf(header_buf + len, left,"%s", "\r\n");

    struct iovec iv[2];
    iv[0].iov_base = header_buf;
    iv[0].iov_len = strlen(header_buf);
    iv[1].iov_base = file_buf;
    iv[1].iov_len = file_size;
    res = writev(clientfd, iv, 2);

    close(fd);
    delete file_buf;

    close(clientfd);
    close(sock);

    std::cout << "exit";
}
TEST(NET, SENDFILE){

}
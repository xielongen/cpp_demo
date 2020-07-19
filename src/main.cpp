#include <iostream>
#include <vector>
#include <array>

#include <util.h>
#include <network.h>
#include <thread>
#include <assert.h>
#include <errno.h>

void send_data(size_t message_len, int millisecond=0, int message_count=1000){
    TcpClient client("127.0.0.1", 10001);
    char* buffer = new char[1024 * 1024];
    if(client.Connect()){
        while (message_count){
            client.Write(buffer, message_len);
            std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
            message_count--;
        }
    }
}
void self_connect(){
    TcpClient client("127.0.0.1", 10001);
    for(int i=0; i < 65536; i++){
        if(client.Connect())
        {
            std::cout << "connect success" << std::endl;
            break;
        }
    }
}

class EchoClient: Actor{
public:
    EchoClient(int client_fd):Actor(client_fd){}
    void operator()(){
        const int buffer_size = 1024 * 10;
        char* buffer = new char[buffer_size];
        while(true){
            zero(buffer, buffer_size);
            ssize_t count = Read(buffer, buffer_size);
            if(count <= 0){
                std::cout << "Read failed " << sock_fd << std::endl;
                std::cout << strerror(errno) << std::endl;
                break;
            }
            else{
                std::cout << "Recv " << count  << " : " << std::string(buffer) << std::endl;
            }

            if(count > 0){
                count = Write(buffer, count);
                if(count == -1){
                    std::cout << "Write failed " << sock_fd << std::endl;
                    std::cout << strerror(errno) << std::endl;
                    break;
                }
            }
        }
    }
};

int main(int argc, char* argv[]){
    std::cout << std::atoi("0.0") << std::endl;
//    UdpServer<RoundServer>(10001, "localhost").run();
//    TcpServer<EchoClient>(10001, "localhost", 10).run();
//    self_connect();
//    int buffer_size = std::atoi(argv[1]);
//    int message_count = std::atoi(argv[2]);
//    std::cout << buffer_size << ", " << message_count << std::endl;
//    send_data(buffer_size, 0, message_count);
//    self_connect();
}
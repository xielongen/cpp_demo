#include <assert.h>
#include <network.h>
#include <util.h>

class RoundServer{
public:
    bool operator()(char* buffer, ssize_t* count, int ip, int port){
        assert(*count == sizeof(TimeMessage));
        TimeMessage* message = (TimeMessage*) buffer;
        std::cout << "IP: " << inet_ntoa(*(in_addr*)&ip)
                  << " Port: " << ntohs(port)
                  << " Content: " << message->send_t
                  << " Count: " << *count
                  << std::endl;
        message->recv_t = now();
        return true;
    }
};
void RunRoundtripServer(std::string ip, int port){
    UdpServer<RoundServer>(port, ip).run();
}

int main(int argc, char* argv[]) {
    RunRoundtripServer(argv[1], std::atoi(argv[2]));
}


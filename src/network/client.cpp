#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/time.h>

#include <array>
#include <numeric>

#include <thread>
#include <network.h>
#include <util.h>

void run_roundtrip_client(std::string ip, int port) {
    UdpClient client(ip, port);
    TimeMessage message;

    std::array<int, 10> time_delta;
    int index = 0;

    while (true) {
        message.send_t = now();
        client.Write(message);
        client.Read(message);
        auto now_t = now();
        auto delta = (message.send_t + now_t) / 2 - message.recv_t;
        time_delta[index] = delta;
        index = (index + 1) % time_delta.size();

        auto mean = std::accumulate(time_delta.begin(), time_delta.end(), 0) * 1.0 / time_delta.size();
        std::cout << " roundtrip: " << now_t - message.send_t
        << " delta: " << delta
        << " mean: " << mean << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char *argv[]) {
    run_roundtrip_client(argv[1], std::atoi(argv[2]));
}


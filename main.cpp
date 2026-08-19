#include <fmt/core.h>
#include <arpa/inet.h>
#include <exception>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h> // for close(fd)
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "headers/types/ipHeader.hpp"
#include "headers/builders/ipHeaderBuilder.hpp"

using namespace std;


int main() {
    // get fd
    // int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    // if(sock < 0) {
    //     cout << "socket() failed: " << strerror(errno) << endl;
    //     return 1;
    // }
    
    // // include handcrafted ip header in buffer sent
    // int enable = 1;
    // int optSetResult = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable));
    // if(optSetResult < 0) {
    //     cout << "setsockopt() failed: " << strerror(errno) << endl;
    //     return 1;
    // }

    // close(sock);

    string data = "hot fish hot fish";

    auto iphdr = IpHeaderBuilder()
        .SetLength(data.length())
        .SetSource("127.0.0.1")
        .SetDestination("127.0.0.1")
        .Build();
    auto bytes = iphdr->getBytes();
    for(const auto byte : bytes) {
        cout << static_cast<int>(byte) << " ";
    }
    return 0;
}
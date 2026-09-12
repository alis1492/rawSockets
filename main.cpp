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
#include "headers/types/udpHeader.hpp"

using namespace std;


int main() {
    // get fd
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(sock < 0) {
        cout << "socket() failed: " << strerror(errno) << endl;
        return 1;
    }
    
    // include handcrafted ip header in buffer sent
    int enable = 1;
    int optSetResult = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable));
    if(optSetResult < 0) {
        cout << "setsockopt() failed: " << strerror(errno) << endl;
        return 1;
    }

    sockaddr_in netcatAddress;
    netcatAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    netcatAddress.sin_family = AF_INET;
    netcatAddress.sin_port = htons(6666);
    socklen_t netcatAddressSize = sizeof(netcatAddress);


    string data = "hot fish hot fish\n";

    auto iphdr = IpHeaderBuilder()
        .SetLength(data)
        .SetSource("127.0.0.1")
        .SetDestination("127.0.0.1")
        .Build();
    auto iphdrBytes = iphdr->getBytes();

    UdpHeader udphdr(data.data(), data.size());
    udphdr.setSourcePort(1234);
    udphdr.setDestinationPort(6666);
    udphdr.setPseudoSource(127, 0, 0, 1);
    udphdr.setPseudoDestination(127, 0, 0, 1);
    udphdr.setLengthByData(data.size());
    // udphdr.setChecksum();
    auto packet = udphdr.getPacket();
    
    vector<uint8_t> bytes(iphdrBytes.begin(), iphdrBytes.end());
    bytes.insert(bytes.end(), packet.begin(), packet.end());

    size_t bytesSent = sendto(sock, bytes.data(), bytes.size(), 0, (sockaddr*)&netcatAddress, netcatAddressSize);
    cout << bytesSent << endl;
    close(sock);
    return 0;
}
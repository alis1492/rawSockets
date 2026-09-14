#include <string>
#include <vector>
#include <iostream>
#include "headers/builders/udpPacketBuilder.hpp"

int main() {
    string data = "hot fish hot fish\n";
    cout << "runs1" << endl;

    auto bytes = UdpPacketBuilder()
        .SetSource("127.0.0.1", 1234)
        .SetDestination("127.0.0.1", 6666)
        .SetData(data.data(), data.size())
        .Build()->getBytes();
    cout << "runs2" << endl;
    for(const auto byte : bytes) 
        printf("%2X ", byte);
    return 0;
}
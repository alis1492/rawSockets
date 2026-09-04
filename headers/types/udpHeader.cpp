#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdint>
#include "ipHeader.hpp"

using namespace std;

class UdpHeader {
    vector<uint8_t> bytes;
    vector<uint8_t> pseudo;
public:
    UdpHeader()
        : bytes(8, 0)
        , pseudo(12, 0) 
    {
        pseudo[8] = 0;
    }

    // pseudoHeader territory
    void setPseudoSource(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4) {
        pseudo[0] = ip1;
        pseudo[1] = ip2;
        pseudo[2] = ip3;
        pseudo[3] = ip4;
    }

    string getPseudoSource() const {
        return to_string(pseudo[0]) + "."
            + to_string(pseudo[1]) + "."
            + to_string(pseudo[2]) + "."
            + to_string(pseudo[3]);
    }

    void setPseudoDestination(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4) {
        pseudo[4] = ip1;
        pseudo[5] = ip2;
        pseudo[6] = ip3;
        pseudo[7] = ip4;
    }

    string getPseudoDestination() const {
        return to_string(pseudo[4]) + "."
            + to_string(pseudo[5]) + "."
            + to_string(pseudo[6]) + "."
            + to_string(pseudo[7]);
    }

    void setPseudoProtocol(Protocol proto) {
        pseudo[9] = static_cast<uint8_t>(proto);
    }

    Protocol getPseudoProtocol() const {
        return static_cast<Protocol>(pseudo[9]);
    }

    void setPseudoLength() {
        uint16_t length = getLength();
        bytes[10] = (length >> 8) & 0xFF;
        bytes[11] = length & 0xFF;
    }


    // udpHeader territory
    void setSourcePort(uint16_t port) {
        bytes[0] = (port >> 8) & 0xFF;
        bytes[1] = port & 0xFF;
    }

    uint16_t getSourcePort() const {
        return (static_cast<uint16_t>(bytes[0]) << 8) | bytes[1];
    }

    void setDestinationPort(uint16_t port) {
        bytes[2] = (port >> 8) & 0xFF;
        bytes[3] = port & 0xFF;
    }

    uint16_t getDestination() const {
        return (static_cast<uint16_t>(bytes[2]) << 8) | bytes[3];
    }

    void setLength(uint16_t length) {
        bytes[4] = (length >> 8) & 0xFF;
        bytes[5] = length & 0xFF;
        setPseudoLength();
    }

    void setLengthByData(int dataSize) {
        setLength(static_cast<uint16_t>(dataSize + 8));
    }

    uint16_t getLength() const {
        return (static_cast<uint16_t>(bytes[4]) << 8) | bytes[5];
    }

    void setChecksumToZero() {
        bytes[6] = 0;
        bytes[7] = 0;
    }

    void setChecksum() {
        setChecksumToZero();
        
    }

    uint16_t getChecksum() const {

    };

    vector<uint8_t> getBytes() const {
        return bytes;
    }
};

int main() {
    UdpHeader udphdr;
    udphdr.setSourcePort(1234);
    udphdr.setDestinationPort(6666);
    auto bytes = udphdr.getBytes();
    for(const auto byte : bytes) {
        printf("%2X ", byte);
    }
}
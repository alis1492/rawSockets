#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdint>
#include "ipHeader.hpp"
#include <memory>

using namespace std;

class UdpHeader {
    vector<uint8_t> bytes;
    vector<uint8_t> pseudo;
    vector<uint8_t> data;
public:
    // Constructors
    template<typename T>
    UdpHeader(const T& _data, size_t _dataLen)
        : bytes(8, 0)
        , pseudo(12, 0)
    {
        setData(_data, _dataLen);

        pseudo[8] = 0;

        setPseudoProtocol(Protocol::udp);
    }
    UdpHeader() 
        : bytes(8, 0)
        , pseudo(12, 0)
    {
        pseudo[8] = 0;

        setPseudoProtocol(Protocol::udp);
    }

    // Set data, takes whatever the hell user sends and converts it to bytes
    template<typename T>
    void setData(const T& _data, size_t _dataLen) {
        uint8_t* ptr = reinterpret_cast<uint8_t*>(_data);
        data.assign(ptr, ptr + _dataLen);
    }

    vector<uint8_t> getData() const { return data; }

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
        pseudo[10] = (length >> 8) & 0xFF;
        pseudo[11] = length & 0xFF;
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

    uint16_t calculateChecksum() {
        setChecksumToZero();
        uint32_t sum = 0;

        // add udp header
        for(int i = 0; i < bytes.size(); i += 2) {
            sum += (static_cast<uint16_t>(bytes[i]) << 8) | bytes[i+1];
            if(sum & 0xFFFF0000) 
                sum = (sum & 0xFFFF) + (sum >> 16);
        }
        // add pseudoHeader
        for(int i = 0; i < pseudo.size(); i += 2) {
            sum += (static_cast<uint16_t>(pseudo[i]) << 8) | pseudo[i+1];
            if(sum & 0xFFFF0000) 
                sum = (sum & 0xFFFF) + (sum >> 16);
        }
        // add data
        for(int i = 0; i < data.size(); i += 2) {
            if(i+1 < data.size())
                sum += (static_cast<uint16_t>(data[i]) << 8) | data[i+1];
            else
                sum += (static_cast<uint16_t>(data[i]) << 8);
            if(sum & 0xFFFF0000) 
                sum = (sum & 0xFFFF) + (sum >> 16);
        }

        return static_cast<uint16_t>(~sum);
    }

    void setChecksum() {
        uint16_t sum = calculateChecksum();
        bytes[6] = (sum >> 8) & 0xFF;
        bytes[7] = sum & 0xFF;
    }

    uint16_t getChecksum() const {
        return (static_cast<uint16_t>(bytes[6]) << 8) | bytes[7];
    };

    vector<uint8_t> getBytes() const {
        return bytes;
    }

    vector<uint8_t> getPacket() const {
        vector<uint8_t> _bytes = bytes;
        _bytes.insert(_bytes.end(), data.begin(), data.end());
        return _bytes;
    }
};

// int main() {
//     string data = "hot fish hot fish";
//     UdpHeader udphdr(data.data(), data.size());
//     udphdr.setSourcePort(1234);
//     udphdr.setDestinationPort(6666);
//     udphdr.setPseudoSource(127, 0, 0, 1);
//     udphdr.setPseudoDestination(127, 0, 0, 1);
//     udphdr.setLengthByData(data.size());
//     udphdr.setChecksum();
//     auto bytes = udphdr.getBytes();
//     for(const auto byte : bytes) {
//         printf("%2X ", byte);
//     }
// }
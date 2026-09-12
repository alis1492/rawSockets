#pragma once
#include <cinttypes>
#include "ipHeader.hpp"
#include <vector>

using namespace std;

class UdpHeader {
    vector<uint8_t> bytes;
    vector<uint8_t> pseudo;
    vector<uint8_t> data;
public:
    // Constructors
    UdpHeader(const void* _data, size_t _dataLen);
    UdpHeader();

    // Set data, takes whatever the hell user sends as bytes
    void setData(const void* _data, size_t _dataLen);

    vector<uint8_t> getData() const;

    // pseudoHeader territory
    void setPseudoSource(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);

    string getPseudoSource() const;

    void setPseudoDestination(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);

    string getPseudoDestination() const;

    void setPseudoProtocol(Protocol proto);

    Protocol getPseudoProtocol() const;

    void setPseudoLength();


    // udpHeader territory
    void setSourcePort(uint16_t port);

    uint16_t getSourcePort() const;

    void setDestinationPort(uint16_t port);

    uint16_t getDestination() const;

    void setLength(uint16_t length);

    void setLengthByData(int dataSize);

    uint16_t getLength() const;

    void setChecksumToZero();

    uint16_t calculateChecksum();

    void setChecksum();

    uint16_t getChecksum() const;

    vector<uint8_t> getBytes() const;

    vector<uint8_t> getPacket() const;
};
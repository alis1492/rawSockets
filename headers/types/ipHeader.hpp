#pragma once
#include <vector>
#include <string>
#include <cstdint>

enum class Protocol : uint8_t {
    udp = 17,   // IPPROTO_UDP
    tcp = 6     // IPPROTO_TCP
};

class IpHeader {
private:
    std::vector<uint8_t> bytes;

public:
    // Constructor
    IpHeader();

    // Setters
    void setProtocolVersion(uint8_t version);
    void setHeaderSize(uint8_t sizeInBytes);
    void setDSField(uint8_t field);
    void setFragmentationFlags(uint8_t flags);
    void setFragmentationOffset(uint8_t offset);
    void setTTL(uint8_t ttl);
    void setProtocol(Protocol protocol);
    void setSource(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);
    void setDestination(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4);
    void setLength(uint16_t length);
    void setLengthByData(uint16_t dataSize);
    void setChecksumToZero();
    void setChecksum();

    // Getters
    int getProtocolVersion() const;
    int getHeaderSize() const;
    int getDSField() const;
    int getFragmentationFlags() const;
    int getFragmentationOffset() const;
    int getTTL() const;
    int getProtocol() const;
    std::string getSource() const;
    std::string getDestination() const;
    int getLength() const;
    int getChecksum() const;
    std::vector<uint8_t> getBytes() const;

    // Checksum calculation
    uint16_t calculateChecksum();
};
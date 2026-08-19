#include "ipHeader.hpp"
#include <iostream>
#include <cstring>

IpHeader::IpHeader() 
    : bytes(20, 0) 
{
    setProtocolVersion(4);
    setHeaderSize(20);
    setDSField(0);
    bytes[4] = 0x00;
    bytes[5] = 0x00; // identification
    setFragmentationFlags(0);
    setFragmentationOffset(0);
    setTTL(64);
    setProtocol(Protocol::udp);
    setSource(127, 0, 0, 1);
    setDestination(127, 0, 0, 1);
}

void IpHeader::setProtocolVersion(uint8_t version) {
    // Preserve the lower 4 bits (IHL) and set upper 4 bits to version
    bytes[0] = (bytes[0] & 0x0F) | ((version & 0x0F) << 4);
}

int IpHeader::getProtocolVersion() const {
    return (bytes[0] >> 4) & 0x0F;
}

void IpHeader::setHeaderSize(uint8_t sizeInBytes) {
    // sizeInBytes / 4 gives the number of 32-bit words
    uint8_t ihl = sizeInBytes / 4;
    // Preserve upper 4 bits (version) and set lower 4 bits to IHL
    bytes[0] = (bytes[0] & 0xF0) | (ihl & 0x0F);
}

int IpHeader::getHeaderSize() const {
    return (bytes[0] & 0x0F) * 4; // Return in bytes
}

void IpHeader::setDSField(uint8_t field) {
    bytes[1] = field;
}

int IpHeader::getDSField() const {
    return bytes[1];
}

void IpHeader::setFragmentationFlags(uint8_t flags) {
    bytes[6] = flags;
}

int IpHeader::getFragmentationFlags() const {
    return bytes[6];
}

void IpHeader::setFragmentationOffset(uint8_t offset) {
    bytes[7] = offset;
}

int IpHeader::getFragmentationOffset() const {
    return bytes[7];
}

void IpHeader::setTTL(uint8_t ttl) {
    bytes[8] = ttl;
}

int IpHeader::getTTL() const {
    return bytes[8];
}

void IpHeader::setProtocol(Protocol protocol) {
    bytes[9] = static_cast<uint8_t>(protocol);
}

int IpHeader::getProtocol() const {
    return bytes[9];
}

void IpHeader::setSource(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4) {
    bytes[12] = ip1;
    bytes[13] = ip2;
    bytes[14] = ip3;
    bytes[15] = ip4;
}

std::string IpHeader::getSource() const {
    return std::to_string(bytes[12]) + "."
         + std::to_string(bytes[13]) + "."
         + std::to_string(bytes[14]) + "."
         + std::to_string(bytes[15]);
}

void IpHeader::setDestination(uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4) {
    bytes[16] = ip1;
    bytes[17] = ip2;
    bytes[18] = ip3;
    bytes[19] = ip4;
}

std::string IpHeader::getDestination() const {
    return std::to_string(bytes[16]) + "."
         + std::to_string(bytes[17]) + "."
         + std::to_string(bytes[18]) + "."
         + std::to_string(bytes[19]);
}

void IpHeader::setLength(uint16_t length) {
    bytes[2] = (length >> 8) & 0xFF;
    bytes[3] = length & 0xFF;
}

void IpHeader::setLengthByData(uint16_t dataSize) {
    uint16_t length = getHeaderSize(); // Already in bytes from getHeaderSize()
    
    if (bytes[9] == static_cast<uint8_t>(Protocol::udp)) {
        length += 8; // UDP header size
    }
    // For TCP: length += 20; // TCP header size (with no options)
    
    length += dataSize;
    setLength(length);
}

int IpHeader::getLength() const {
    int result = (static_cast<int>(bytes[2]) << 8);
    result += bytes[3];
    return result;
}

void IpHeader::setChecksumToZero() {
    bytes[10] = 0;
    bytes[11] = 0;
}

uint16_t IpHeader::calculateChecksum() {
    setChecksumToZero();
    uint32_t sum = 0;
    
    // Sum all 16-bit words in the header
    for (size_t i = 0; i < bytes.size(); i += 2) {
        uint16_t word = (bytes[i] << 8) | bytes[i + 1];
        sum += word;
        
        // End-around carry
        if (sum & 0xFFFF0000) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
    }
    
    // One's complement
    return static_cast<uint16_t>(~sum & 0xFFFF);
}

void IpHeader::setChecksum() {
    uint16_t sum = calculateChecksum();
    bytes[10] = (sum >> 8) & 0xFF;
    bytes[11] = sum & 0xFF;
}

int IpHeader::getChecksum() const {
    int result = static_cast<int>(bytes[10]) << 8;
    result += bytes[11];
    return result;
}

std::vector<uint8_t> IpHeader::getBytes() const {
    return bytes;
}
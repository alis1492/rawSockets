#pragma once
#include "../types/udpPacket.hpp"

using namespace std;

class UdpPacketBuilder {
    shared_ptr<UdpPacket> udpPacket;
    string sourceIp;
    uint16_t sourcePort;
    string destinationIp;
    uint16_t destinationPort;
    void* data;
    size_t size;
public:
    // default constructor
    UdpPacketBuilder();

    /// @brief Step 1. Set Source ip and port of the packet
    /// @param ip 127.0.0.1 string format
    /// @param port port number
    /// @return UdpPacketBuilder& this
    UdpPacketBuilder& SetSource(string ip, uint16_t port);

    /// @brief Step 2. Set Destination ip and port of the packet
    /// @param ip 127.0.0.1 string format
    /// @param port port number
    /// @return UdpPacketBuilder& this
    UdpPacketBuilder& SetDestination(string ip, uint16_t port);

    /// @brief Step 3. Set data with a pointer towards it and its size
    /// @param data the pointer to the actual data. For example: string.data()
    /// @param size data length, must not insclude \0. For example: string.size()
    /// @return UdpPacketBuilder& this
    UdpPacketBuilder& SetData(void* data, size_t size);

    // Step 4. Build a UdpPacket ready for sending via UdpPacket.getBytes()
    shared_ptr<UdpPacket> Build();
};
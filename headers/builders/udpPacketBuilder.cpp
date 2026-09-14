#include "../types/udpPacket.hpp"
#include "udpPacketBuilder.hpp"

using namespace std;

// default constructor
UdpPacketBuilder::UdpPacketBuilder() 
    : udpPacket(make_shared<UdpPacket>())
{}

/// @brief Step 1. Set Source ip and port of the packet
/// @param ip 127.0.0.1 string format
/// @param port port number
/// @return UdpPacketBuilder& this
UdpPacketBuilder& UdpPacketBuilder::SetSource(string ip, uint16_t port) {
    sourceIp = ip;
    sourcePort = port;
    return *this;
}

/// @brief Step 2. Set Destination ip and port of the packet
/// @param ip 127.0.0.1 string format
/// @param port port number
/// @return UdpPacketBuilder& this
UdpPacketBuilder& UdpPacketBuilder::SetDestination(string ip, uint16_t port) {
    destinationIp = ip;
    destinationPort = port;
    return *this;
}

/// @brief Step 3. Set data with a pointer towards it and its size
/// @param data the pointer to the actual data. For example: string.data()
/// @param size data length, must not insclude \0. For example: string.size()
/// @return UdpPacketBuilder& this
UdpPacketBuilder& UdpPacketBuilder::SetData(void* _data, size_t _size) {
    data = _data;
    size = _size;
    return *this;
}

// Step 4. Build a UdpPacket ready for sending via UdpPacket.getBytes()
shared_ptr<UdpPacket> UdpPacketBuilder::Build() {
    udpPacket->setIpHeader(
        IpHeaderBuilder()
            .SetSource(sourceIp)
            .SetDestination(destinationIp)
            .SetLength(static_cast<uint16_t>(size))
            .Build()
    );
    udpPacket->setUdpHeader(
        UdpHeaderBuilder()
        .SetSource(sourceIp, sourcePort)
        .SetDestination(destinationIp, destinationPort)
        .SetData(data, size)
        .Build()
    );
    return udpPacket;
}
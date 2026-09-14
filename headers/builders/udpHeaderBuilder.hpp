#pragma once
#include "../types/udpHeader.hpp"
#include <memory>

using namespace std;

class UdpHeaderBuilder {
    shared_ptr<UdpHeader> udphdr;
public:
    /// @brief Dafault constructor
    UdpHeaderBuilder();

    /// @brief Step 1. Sets data
    /// @param data const void* any data
    /// @param size data length, must not insclude \0. For example string.size()
    /// @return UdpHeaderBuilder this
    UdpHeaderBuilder& SetData(const void* data, size_t size);

    /// @brief Step 2. Set UdpHeader Source port and pseudo Source ip
    /// @param ip 127.0.0.1 string format
    /// @param port uint16_t port number
    /// @return UdpHeaderBuilder this
    UdpHeaderBuilder& SetSource(string ip, uint16_t port);

    /// @brief Step 3. Set UdpHeader Destination port and pseudo Destination ip
    /// @param ip 127.0.0.1 string format
    /// @param port uint16_t port number
    /// @return UdpHeaderBuilder this
    UdpHeaderBuilder& SetDestination(string ip, uint16_t port);

    /// @brief Step 4. Builds the UdpHeader. Sets length and calculates the checksum
    /// @return 
    shared_ptr<UdpHeader> Build();
};
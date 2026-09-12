#include "../types/udpHeader.hpp"
#include "udpHeaderBuilder.hpp"
#include <memory>

using namespace std;

UdpHeaderBuilder::UdpHeaderBuilder()
    : udphdr(make_shared<UdpHeader>())
{}

/// @brief Step 1. Sets data
/// @param data const void* any data
/// @param size data length, must not insclude \0. For example string.size()
/// @return UdpHeaderBuilder this
UdpHeaderBuilder& UdpHeaderBuilder::SetData(const void* data, size_t size) {
    udphdr->setData(data, size);
    return *this;
}

/// @brief Step 2. Set UdpHeader Source port and pseudo Source ip
/// @param ip 127.0.0.1 string format
/// @param port uint16_t port number
/// @return UdpHeaderBuilder this
UdpHeaderBuilder& UdpHeaderBuilder::SetSource(string ip, uint16_t port) {
    // extract uint8_t values from ip string
    uint8_t ip1 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip2 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip3 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip4 = stoul(ip);

    udphdr->setPseudoSource(ip1, ip2, ip3, ip4);
    udphdr->setSourcePort(port);
    return *this;
}

/// @brief Step 3. Set UdpHeader Destination port and pseudo Destination ip
/// @param ip 127.0.0.1 string format
/// @param port uint16_t port number
/// @return UdpHeaderBuilder this
UdpHeaderBuilder& UdpHeaderBuilder::SetDestination(string ip, uint16_t port) {
    // extract uint8_t values from ip string
    uint8_t ip1 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip2 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip3 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip4 = stoul(ip);

    udphdr->setPseudoDestination(ip1, ip2, ip3, ip4);
    udphdr->setDestinationPort(port);
    return *this;
}

/// @brief Step 4. Builds the UdpHeader. Sets length and calculates the checksum
/// @return 
shared_ptr<UdpHeader> UdpHeaderBuilder::Build() {
    udphdr->setLengthByData(udphdr->getData().size());
    udphdr->setChecksum();
    return udphdr;
}
#include "ipHeader.hpp"
#include "udpHeader.hpp"
#include "../builders/udpHeaderBuilder.hpp"
#include "../builders/ipHeaderBuilder.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "udpPacket.hpp"

using namespace std;

// i thought of naming it InetPacket, but then thought it would be cool to make InetPacket the base class
// but inheritance is kinda smelly so ig ill stick around with this
void UdpPacket::setIpHeader(const shared_ptr<IpHeader> _iphdr) {
    iphdr = _iphdr;
}

shared_ptr<IpHeader> UdpPacket::getIpHeader() const { return iphdr; }

void UdpPacket::setUdpHeader(const shared_ptr<UdpHeader> _udphdr) {
    udphdr = _udphdr;
}

shared_ptr<UdpHeader> UdpPacket::getUdpHeader() const { return udphdr; }

vector<uint8_t> UdpPacket::getBytes() const {
    vector<uint8_t> bytes = iphdr->getBytes();
    vector<uint8_t> udpBytes = udphdr->getPacket();
    bytes.insert(bytes.end(), udpBytes.begin(), udpBytes.end());
    return bytes;
}
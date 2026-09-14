#pragma once
#include "ipHeader.hpp"
#include "udpHeader.hpp"
#include "../builders/udpHeaderBuilder.hpp"
#include "../builders/ipHeaderBuilder.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

// i thought of naming it InetPacket, but then thought it would be cool to make InetPacket the base class
// but inheritance is kinda smelly so ig ill stick around with this
// This is self documenting
class UdpPacket {
    shared_ptr<IpHeader> iphdr;
    shared_ptr<UdpHeader> udphdr;
public:
    void setIpHeader(const shared_ptr<IpHeader> _iphdr);

    shared_ptr<IpHeader> getIpHeader() const;

    void setUdpHeader(const shared_ptr<UdpHeader> _udphdr);

    shared_ptr<UdpHeader> getUdpHeader() const;

    vector<uint8_t> getBytes() const;
};
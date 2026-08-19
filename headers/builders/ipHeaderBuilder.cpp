#include "../types/ipHeader.hpp"
#include "../builders/ipHeaderBuilder.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

IpHeaderBuilder::IpHeaderBuilder() 
    : iphdr(make_shared<IpHeader>()) {}
    
IpHeaderBuilder& IpHeaderBuilder::SetLength(uint16_t dataSize) {
    iphdr->setLengthByData(dataSize);
    return *this;
}

IpHeaderBuilder& IpHeaderBuilder::SetLength(string str) {
    iphdr->setLengthByData(str.length());
    return *this;
}

IpHeaderBuilder& IpHeaderBuilder::SetSource(string ip) {
    // extract uint8_t values from ip string
    uint8_t ip1 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip2 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip3 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip4 = stoul(ip);

    iphdr->setSource(ip1, ip2, ip3, ip4);
    return *this;
}

IpHeaderBuilder& IpHeaderBuilder::SetDestination(string ip) {
    // extract uint8_t values from ip string
    uint8_t ip1 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip2 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip3 = stoul(ip.substr(0, ip.find_first_of(".")));
    ip = ip.substr(ip.find_first_of(".")+1, ip.length() - ip.find_first_of("."));
    uint8_t ip4 = stoul(ip);

    iphdr->setDestination(ip1, ip2, ip3, ip4);
    return *this;
}

shared_ptr<IpHeader> IpHeaderBuilder::Build() {
    iphdr->setChecksum();
    return iphdr;
}
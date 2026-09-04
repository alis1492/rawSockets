#pragma once
#include "../types/ipHeader.hpp"
#include <string>
#include <memory>

using namespace std;

class IpHeaderBuilder {
private:
    shared_ptr<IpHeader> iphdr;
public:
    IpHeaderBuilder();

    /// @brief set Ip Header length attribute
    /// @param dataSize size of whatever data is sent, for example string.length()
    /// @return IpHeaderBuilder this
    IpHeaderBuilder& SetLength(uint16_t dataSize);

    /// @brief set Ip Header length attribute based on a string provided
    /// @param str string data thats about to be sent
    /// @return IpHeaderBuilder this
    IpHeaderBuilder& SetLength(string str);

    /// @brief set Ip Header source
    /// @param ip 127.0.0.1 string format
    /// @return IpHeaderBuilder this
    IpHeaderBuilder& SetSource(string ip);

    /// @brief set Ip Header destination
    /// @param ip 127.0.0.1 string format
    /// @return IpHeaderBuilder this
    IpHeaderBuilder& SetDestination(string ip);

    /// @brief Calculate the checksum and build the IpHeader
    /// @return shared_ptr<IpHeader> iphdr
    shared_ptr<IpHeader> Build();
};
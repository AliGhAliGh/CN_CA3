#include "IP.h"

#include <iostream>
#include <sstream>

AbstractIP::AbstractIP(QObject *parent) :
    QObject {parent}
{}

UT::IP<UT::IPVersion::IPv4>::IP(QObject *parent) :
    AbstractIP(parent)
{
    m_value.set();
}

UT::IP<UT::IPVersion::IPv4>::IP(std::bitset<32> ipValue, QObject *parent) :
    AbstractIP(parent)

{
    m_value = ipValue;
}

UT::IP<UT::IPVersion::IPv4>::IP(const QString &ipString, QObject *parent) :
    AbstractIP(parent)
{
    auto list = ipString.split(".");
    if(list.size() != 4) throw new std::invalid_argument("Bad Ip String!");
    auto ok = new bool;
    for(int i = 0; i < 4; ++i)
    {
        auto num = list.at(i).toUInt(ok);
        if(!ok) throw new std::invalid_argument("Bad Number!");
        if(num > 255) throw new std::invalid_argument("Out Of Range Num!");
        auto bits = std::bitset<8>(num);
        for(int j = 0; j < 8; ++j)
            m_value.set(8 * i + j, bits.test(j));
    }
}

UT::IP<UT::IPVersion::IPv4>::IP(uint32_t ipValue, QObject *parent) :
    AbstractIP(parent)
{
    m_value = std::bitset<32>(ipValue);
}

std::string
UT::IP<UT::IPVersion::IPv4>::to_string() const
{
    auto        divider = std::bitset<32>(255);
    std::string res     = "";
    for(auto i = 3; i >= 0; i--)
    {
        std::stringstream temp;
        int               offset = 8 * i;
        temp << ((m_value >> offset) & divider).to_ulong();
        res = temp.str() + res;
        if(i != 0) res = '.' + res;
    }
    return res;
}

UT::IP<UT::IPVersion::IPv4>::~IP() {};

/**
 * ===========================================
 * ===========================================
 * ===========================================
 * @brief The IP class for IPv6.
 * ===========================================
 * ===========================================
 * ===========================================
 */

UT::IP<UT::IPVersion::IPv6>::IP(QObject *parent) :
    AbstractIP(parent)
{
    value.set();
}

UT::IP<UT::IPVersion::IPv6>::IP(const QString &ipString, QObject *parent) :
    AbstractIP(parent)
{
    auto list = ipString.split(":");
    if(list.size() != 8) throw new std::invalid_argument("Bad Ip String!");
    for(int i = 0; i < 8; ++i)
    {
        auto byteValue = static_cast<uint16_t>(stoi(list[i].toStdString()));
        auto bits      = std::bitset<16>(byteValue);
        for(int j = 0; j < 16; ++j)
            value.set(16 * i + j, bits.test(j));
    }
}

// IP<UT::IPVersion::IPv6>::IP(uint64_t ipValue, QObject *parent) :
//     AbstractIP(parent)
// {
//     m_ipValue = ipValue;
//     fromIPValue(ipValue);
//     toStringImpl();
// }

std::string
UT::IP<UT::IPVersion::IPv6>::to_string() const
{
    auto        divider = std::bitset<128>(15);
    std::string res     = "";
    for(auto i = 31; i >= 0; i--)
    {
        std::stringstream temp;
        int               offset = 4 * (4 * (i / 4) + (3 - (i % 4)));
        temp << std::hex << std::uppercase << ((value >> offset) & divider).to_ulong();
        res = temp.str() + res;
        if(i % 4 == 0 && i != 0) res = ':' + res;
    }
    return res;
}

UT::IP<UT::IPVersion::IPv6>::~IP() {};

std::bitset<32>
UT::IP<UT::IPVersion::IPv4>::getData()
{
    return m_value;
}

#include "src/algorithm/dhcp.h"

#include <QDebug>

DHCPServer::DHCPServer(QObject *parent) :
    QObject(parent)
{}

void
DHCPServer::init(IPPtr_t base)
{
    auto data  = (base.dynamicCast<UT::IPv4Ptr_t>()).get()->get()->getData();
    data      &= 0xffffff00;
    for(int i = 1; i < 256; ++i)
    {
        std::bitset<32> temp  = data;
        temp                 |= i;
        m_ipPool.push_back(IPPtr_t(new UT::IPv4_t(temp)));
    }
}

IPPtr_t
DHCPServer::handleDiscovery(const MacAddressPtr_t &macAddress)
{
    if(m_allocatedIps.contains(macAddress)) return m_allocatedIps[macAddress];

    if(!m_ipPool.isEmpty())
    {
        auto allocatedIp = m_ipPool.takeFirst();
        m_allocatedIps.insert(macAddress, allocatedIp);
        return allocatedIp;
    }

    return nullptr;
}

IPPtr_t
DHCPServer::handleRequest(const MacAddressPtr_t &macAddress)
{
    if(m_allocatedIps.contains(macAddress)) return m_allocatedIps[macAddress];
    return nullptr;
}

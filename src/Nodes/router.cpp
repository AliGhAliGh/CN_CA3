#include "router.h"

#include <QDebug>

Router::Router(uint8_t id, uint bufferSize, QObject *parent) :
    Node {id, parent}, m_isBroken {false}, m_bufferSize {bufferSize}
{
    for(int i = 1; i <= 4; ++i)
        m_ports.append(PortPtr_t(new Port(true, nullptr, i, this)));
}

PortPtr_t
Router::getPort(int id)
{
    if(id > 0 && id <= m_ports.size())
    {
        return m_ports[id - 1];
    }
    qDebug() << "Router" << getId() << ": Invalid port ID" << id;
    return nullptr;
}

PortPtr_t
Router::getFreePort()
{
    for(const auto &port : m_ports)
        if(port->IsFree) return port;
    qDebug() << "Router" << getId() << ": No free ports available!";
    return nullptr;
}

PortPtr_t
Router::setBGP()
{
    PortPtr_t bgpPort = getFreePort();
    if(bgpPort)
    {
        bgpPort->setAsBGP();
        qDebug() << "Router" << getId() << ": BGP activated on port" << bgpPort->getPortNumber();
        return bgpPort;
    }
    qDebug() << "Router" << getId() << ": No free port available for BGP!";
    return nullptr;
}

void
Router::setupDhcp(QString base)
{
    m_dhcp.init(IPPtr_t(new UT::IPv4_t(base)));
}

void
Router::setBroken(bool isBroken)
{
    m_isBroken = isBroken;
    for(const auto &port : m_ports)
    {
        port->setBroken(isBroken);
    }
    // Q_EMIT routerStatusChanged(getId(), isBroken);
    qDebug() << "Router" << getId() << ": Status set to" << (isBroken ? "Broken" : "Operational");
}

void
Router::test()
{
    // for(int i = 0; i < m_ports.size(); ++i)
    //     m_ports[i]->sendPacket(PacketPtr_t(new Packet()));
}

void
Router::sendOspf()
{
    for(auto &port : m_ports)
    {
        if(port->isBgp()) continue;
        auto packet = PacketPtr_t(Packet::OspfPacket(NodePtr_t(this)));
        port->sendPacket(packet);
    }
}

void
Router::run()
{}

void
Router::tick(unsigned long long num)
{}

void
Router::sendDhcpDiscover()
{}

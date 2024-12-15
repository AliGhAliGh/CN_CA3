#include "Port.h"

Port::Port(bool isRouter, AbstractIP *ip, uint8_t number, QObject *parent) :
    QObject {parent}
{
    m_number   = number;
    m_iP       = ip;
    m_isRouter = isRouter;
    IsFree     = true;
}

Port::~Port() {}

bool
Port::isRouterPort()
{
    return m_isRouter;
}

void
Port::sendPacket(const PacketPtr_t &data)
{
    ++m_numberOfPacketsSent;
    Q_EMIT packetSent(data);
}

void
Port::receivePacket(const PacketPtr_t &data)
{}

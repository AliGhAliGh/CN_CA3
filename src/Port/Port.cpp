#include "Port.h"
#include <QDebug>

Port::Port(bool isRouter, IPPtr_t ip, uint8_t number, QObject *parent) :
    QObject {parent},
    IsFree {true},
    m_number {number},
    m_numberOfPacketsSent {0},
    m_isRouter {isRouter},
    m_iP {ip},
    m_isBGP {false},
    m_isBroken {false}
{
}

Port::~Port() {}

bool
Port::isRouterPort()
{
    return m_isRouter;
}

uint8_t
Port::getPortNumber() const
{
    return m_number;
}

void
Port::setAsBGP()
{
    m_isBGP = true;
    IsFree  = false;
    qDebug() << "Port" << m_number << "is now configured for BGP.";
}

void
Port::setBroken(bool isBroken)
{
    m_isBroken = isBroken;
    qDebug() << "Port" << m_number << (isBroken ? "is broken" : "is operational");
}

bool
Port::isBroken() const
{
    return m_isBroken;
}

bool
Port::isBgp()
{
    return m_isBGP;
}

void
Port::sendPacket(const PacketPtr_t &data)
{
    if (m_isBroken) {
        qDebug() << "Port" << m_number << "is broken. Cannot send packet.";
        return;
    }
    ++m_numberOfPacketsSent;
    Q_EMIT packetSent(data);
}

void
Port::receivePacket(const PacketPtr_t &data)
{
    if (m_isBroken) {
        qDebug() << "Port" << m_number << "is broken. Cannot receive packet.";
        return;
    }
    Q_EMIT packetReceived(data);
}

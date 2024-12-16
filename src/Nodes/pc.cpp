#include "pc.h"

#include <QDebug>

PC::PC(uint8_t id, QObject *parent) :
    Node {id, parent}, m_port {new Port(false, nullptr, 1, this)}
{
    connect(m_port.get(), &Port::receivePacket, this, &PC::receivedPacket);
}

PortPtr_t
PC::getPort()
{
    return m_port;
}

void
PC::sendPacket(const PacketPtr_t &packet)
{
    if(m_port)
    {
        qDebug() << "PC" << getId() << "is sending a packet.";
        m_port->sendPacket(packet);
    }
}

void
PC::receivedPacket(const PacketPtr_t &packet)
{
    if(!packet)
    {
        qDebug() << "PC" << getId() << "received a null packet!";
        return;
    }
    else
    {
        qDebug() << "Packet is not destined for PC" << getId();
    }
}

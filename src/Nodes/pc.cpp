#include "pc.h"
#include <QDebug>

PC::PC(uint8_t id, QObject *parent) :
    Node {id, parent},
    m_port {new Port(false, nullptr, 1, this)} // پورت غیر روتر با شماره 1
{
    connect(m_port.get(), &Port::packetSent, this, [this](const PacketPtr_t &packet) {
        Q_EMIT packetSent(getId(), packet);
    });

    connect(m_port.get(), &Port::receivePacket, this, [this](const PacketPtr_t &packet) {
        this->receivePacket(packet);
    });
}

PortPtr_t
PC::getPort()
{
    return m_port;
}

void
PC::sendPacket(const PacketPtr_t &packet)
{
    if (m_port) {
        qDebug() << "PC" << getId() << "is sending a packet.";
        m_port->sendPacket(packet);
    }
}

void
PC::receivePacket(const PacketPtr_t &packet)
{
    if (!packet) {
        qDebug() << "PC" << getId() << "received a null packet!";
        return;
    }
     else {
        qDebug() << "Packet is not destined for PC" << getId();
    }

    // ارسال سیگنال برای اطلاع‌رسانی دریافت بسته
    Q_EMIT packetReceived(getId(), packet);
}

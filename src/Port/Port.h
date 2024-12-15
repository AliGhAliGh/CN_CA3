#ifndef PORT_H
#define PORT_H

#include "src/Packets/packet.h"

#include <QObject>

class Port : public QObject
{
    Q_OBJECT

public:
    bool IsFree;

    explicit Port(bool isRouter, AbstractIP *ip, uint8_t number, QObject *parent = nullptr);

    ~Port() override;
    bool isRouterPort();

Q_SIGNALS:
    void packetSent(const PacketPtr_t &data);
    void packetReceived(const PacketPtr_t &data);

public Q_SLOTS:
    void sendPacket(const PacketPtr_t &data);
    void receivePacket(const PacketPtr_t &data);

private:
    uint8_t  m_number;
    uint64_t m_numberOfPacketsSent;
    bool        m_isRouter;
    AbstractIP *m_iP;
};

typedef QSharedPointer<Port> PortPtr_t;

#endif    // PORT_H

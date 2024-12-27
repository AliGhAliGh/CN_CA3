#ifndef PORT_H
#define PORT_H

#include "src/Packets/packet.h"

#include <QObject>

class Port : public QObject
{
    Q_OBJECT

public:
    bool IsFree;

    explicit Port(bool isRouter, IPPtr_t ip, uint8_t number, QObject *parent = nullptr);

    ~Port() override;
    bool    isRouterPort();
    uint8_t getPortNumber() const;
    void    setAsBGP();
    void    setBroken(bool isBroken);
    bool    isBroken() const;
    bool    isBgp();

Q_SIGNALS:
    void packetSent(const PacketPtr_t &data);
    void packetReceived(const PacketPtr_t &data);

public Q_SLOTS:
    void sendPacket(const PacketPtr_t &data);
    void receivePacket(const PacketPtr_t &data);

private:
    uint8_t  m_number;
    uint64_t m_numberOfPacketsSent;
    bool     m_isRouter;
    IPPtr_t  m_iP;
    bool     m_isBGP;
    bool     m_isBroken;
};

typedef QSharedPointer<Port> PortPtr_t;

#endif    // PORT_H

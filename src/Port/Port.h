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
    uint8_t getPortNumber() const;
    void setAsBGP();                // تنظیم پورت به عنوان BGP
    void setBroken(bool isBroken);
    bool isBroken() const;

Q_SIGNALS:
    void packetSent(const PacketPtr_t &data);
    void packetReceived(const PacketPtr_t &data);

public Q_SLOTS:
    void sendPacket(const PacketPtr_t &data);
    void receivePacket(const PacketPtr_t &data);

private:
    uint8_t  m_number;
    uint64_t m_numberOfPacketsSent;
    bool     m_isRouter;            // آیا پورت متعلق به روتر است؟
    AbstractIP *m_iP;               // آدرس IP متصل به پورت
    bool     m_isBGP;               // آیا پورت برای BGP تنظیم شده است؟
    bool     m_isBroken;
};

typedef QSharedPointer<Port> PortPtr_t;

#endif // PORT_H

#ifndef PC_H
#define PC_H

#include "node.h"
#include "src/Port/Port.h"

#include <QObject>

class PC : public Node
{
    Q_OBJECT

public:
    explicit PC(uint8_t id, QObject *parent = nullptr);

    PortPtr_t getPort();

    void sendPacket(const PacketPtr_t &packet);
    void receivePacket(const PacketPtr_t &packet);

Q_SIGNALS:
    void packetSent(uint8_t pcId, PacketPtr_t packet);
    void packetReceived(uint8_t pcId, PacketPtr_t packet);

private:
    PortPtr_t m_port; // pc port ????
};

typedef QSharedPointer<PC> PCPtr_t;

#endif // PC_H

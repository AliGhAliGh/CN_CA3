#ifndef PC_H
#define PC_H

#include "node.h"
#include "src/Port/Port.h"

#include <QObject>

class PC : public Node
{
public:
    explicit PC(uint8_t id, QObject *parent = nullptr);

    PortPtr_t getPort();

    void sendPacket(const PacketPtr_t &packet);

private Q_SLOTS:
    void receivedPacket(const PacketPtr_t &packet);

private:
    PortPtr_t m_port;
};

typedef QSharedPointer<PC> PCPtr_t;

#endif // PC_H

#ifndef PACKET_H
#define PACKET_H

#include "Globals.h"
#include "src/IP/IP.h"

#include <QObject>

class Packet : public QObject
{
    Q_OBJECT

public:
    explicit Packet(QObject *parent = nullptr);

private:
    UT::PacketType          type;
    uint                    waiting_cycles;
    uint                    total_cycles;
    QByteArray              payload;
    std::vector<AbstractIP> path;
    UT::TcpHeader           tcpHeader;
    void                   *ipHeader;
    UT::DataLinkHeader      dataLinkHeader;

Q_SIGNALS:
};

typedef QSharedPointer<Packet> PacketPtr_t;

#endif    // PACKET_H

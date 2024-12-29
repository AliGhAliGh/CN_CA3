#ifndef PACKET_H
#define PACKET_H

#include "Globals.h"
#include "src/IP/IP.h"
#include "src/Nodes/node.h"

#include <QObject>

class Packet;

typedef QSharedPointer<Packet> PacketPtr_t;

class Packet : public QObject
{
    Q_OBJECT

public:
    explicit Packet(UT::PacketType type, QString payload, QObject *parent = nullptr);

    static PacketPtr_t OspfPacket(NodePtr_t node);

protected:
    UT::PacketType          m_type;
    uint                    m_waiting_cycles;
    uint                    m_total_cycles;
    QString                 m_payload;
    std::vector<AbstractIP> m_path;
    UT::TcpHeader           m_tcpHeader;
    void                   *m_ipHeader;
    UT::DataLinkHeader      m_dataLinkHeader;
    bool                    m_isIpv4;

Q_SIGNALS:
};

#endif    // PACKET_H

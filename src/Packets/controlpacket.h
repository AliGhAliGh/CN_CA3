#ifndef CONTROLPACKET_H
#define CONTROLPACKET_H

#include "packet.h"

class ControlPacket : public Packet
{
public:
    explicit ControlPacket(UT::PacketControlType type, QString payload, QObject *parent = nullptr);

private:
    UT::PacketControlType m_type;
};

#endif    // CONTROLPACKET_H

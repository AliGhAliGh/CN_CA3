#ifndef DHCPPACKET_H
#define DHCPPACKET_H

#include "controlpacket.h"

class DhcpPacket : public ControlPacket
{
public:
    explicit DhcpPacket(QString payload, QObject *parent = nullptr);
};

#endif    // DHCPPACKET_H

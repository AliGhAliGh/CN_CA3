#include "dhcppacket.h"

DhcpPacket::DhcpPacket(QString payload, QObject *parent) :
    ControlPacket {UT::PacketControlType::DHCPDiscovery, payload, parent}
{}

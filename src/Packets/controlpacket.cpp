#include "controlpacket.h"

ControlPacket::ControlPacket(UT::PacketControlType type, QString payload, QObject *parent) :
    Packet {UT::PacketType::Control, payload, parent}, m_type {type}
{}

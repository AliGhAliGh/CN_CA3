#include "packet.h"

#include "src/Nodes/node.h"

UT::Ipv4Header *
createOSPFHeader(UT::IPv4Ptr_t srcIp, uint16_t payloadSize)
{
    auto header                 = new UT::Ipv4Header();
    header->versionHeaderLength = 20;
    header->typeOfService       = 0;
    header->totalLength         = 20 + payloadSize;
    header->identification      = 0;
    header->flagsFragmentOffset = 0;
    header->ttl                 = 1;
    header->protocol            = 0;    //89;
    header->src                 = srcIp;
    header->dst                 = UT::IPv4Ptr_t(new UT::IPv4_t("0.0.0.0"));
    header->headerChecksum      = 0;
    return header;
}

UT::TcpHeader
createTcpHeader()
{
    UT::TcpHeader header;

    header.sourcePort    = 0;
    header.destPort      = 0;
    header.seqNum        = 0;
    header.ackNum        = 0;
    header.dataOffset    = 20;
    header.flags         = 0x10;
    header.windowSize    = 0;
    header.checkSum      = 0;
    header.urgentPointer = 0;
    return header;
}

Packet::Packet(UT::PacketType type, QString payload, QObject *parent) :
    QObject {parent}, m_type {type}, m_payload {payload}
{
    m_ipHeader       = new UT::Ipv4Header();
    m_isIpv4         = true;
    m_dataLinkHeader = UT::DataLinkHeader {nullptr, nullptr};
    m_tcpHeader      = UT::TcpHeader();
}

PacketPtr_t
Packet::OspfPacket(NodePtr_t node)
{
    auto payload = QString::fromStdString(node.get()->getIp()->to_string());
    payload.append("|");
    auto res                     = new Packet(UT::PacketType::Control, payload);
    res->m_dataLinkHeader.srcMac = MacAddressPtr_t(node->getMac());
    res->m_ipHeader  = createOSPFHeader(UT::IPv4Ptr_t((UT::IPv4_t *)node->getIp()), payload.size());
    res->m_tcpHeader = createTcpHeader();
    return PacketPtr_t(res);
}

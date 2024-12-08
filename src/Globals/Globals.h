#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdint>
#include <QSharedPointer>

namespace UT
{

enum class IPVersion
{
    IPv4,
    IPv6
};

template <UT::IPVersion version>
class IP;

typedef IP<UT::IPVersion::IPv4> IPv4_t;
typedef IP<UT::IPVersion::IPv6> IPv6_t;
typedef QSharedPointer<IPv4_t>  IPv4Ptr_t;
typedef QSharedPointer<IPv6_t>  IPv6Ptr_t;

class MacAddress;
typedef QSharedPointer<MacAddress> MacAddress_t;

enum class PacketType
{
    Data,
    Control
};

enum class PacketControlType
{
    Request,
    Response,
    Acknowledge,
    Error,
    DHCPDiscovery,
    DHCPOffer,
    DHCPRequest,
    DHCPAcknowledge,
    DHCPNak,
    RIP,
    OSPF,
};

enum class DistributionType
{
    Poisson,
    Pareto
};

enum class TopologyType
{
    Mesh,
    RingStar,
    Torus
};

struct Ipv4Header
{
    uint8_t   versionHeaderLength;
    uint8_t   typeOfService;
    uint16_t  totalLength;
    uint16_t  identification;
    uint16_t  flagsFragmentOffset;
    uint8_t   ttl;
    uint8_t   protocol;
    uint16_t  headerChecksum;
    IPv4Ptr_t src;
    IPv4Ptr_t dst;
};

struct Ipv6Header
{
    uint32_t  versionTrafficClassFlowLabel;
    uint16_t  payloadLength;
    uint8_t   nextHeader;
    uint8_t   hopLimit;
    IPv6Ptr_t srcIp;
    IPv6Ptr_t dstIp;
};

struct TcpHeader
{
    uint16_t sourcePort;
    uint16_t destPort;
    uint32_t seqNum;
    uint32_t ackNum;
    uint8_t  dataOffset;
    uint8_t  flags;
    uint16_t windowSize;
    uint16_t checkSum;
    uint16_t urgentPointer;
};

struct DataLinkHeader
{
    MacAddress_t srcMac;
    MacAddress_t dstMac;
};
}    // namespace UT

#endif    // GLOBALS_H

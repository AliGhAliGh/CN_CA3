#ifndef DHCP_SERVER_H
#define DHCP_SERVER_H

#include <src/IP/IP.h>

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

class DHCPServer : public QObject
{
    Q_OBJECT

public:
    explicit DHCPServer(QObject *parent = nullptr);

    void    init(IPPtr_t base);
    IPPtr_t handleDiscovery(const MacAddressPtr_t &macAddress);
    IPPtr_t handleRequest(const MacAddressPtr_t &macAddress);

private:
    QVector<IPPtr_t>               m_ipPool;
    QMap<MacAddressPtr_t, IPPtr_t> m_allocatedIps;
};

#endif    // DHCP_SERVER_H

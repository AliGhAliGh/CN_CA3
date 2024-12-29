#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include "src/IP/macaddress.h"
#include "src/Port/Port.h"

#include <QMap>
#include <QObject>
#include <QQueue>
#include <QVector>

class Router : public Node
{
public:
    explicit Router(uint8_t id, uint bufferSize = 100, QObject *parent = nullptr);

    PortPtr_t getPort(int id);
    PortPtr_t getFreePort();
    PortPtr_t setBGP();
    void      setBroken(bool isBroken = true);
    void      test();
    void      sendOspf();
    QList<PortPtr_t> getPorts() const;


protected:
    void run() override;

protected Q_SLOTS:
    void tick(unsigned long long num) override;

Q_SIGNALS:
    void routerStatusChanged(uint8_t routerId, bool isBroken);

private:
    QVector<PortPtr_t>     m_ports;
    bool                   m_isBroken;
    QQueue<PacketPtr_t>    m_buffer;
    uint                   m_bufferSize;
    QMap<AbstractIP, Port> m_routingTable;
};

typedef QSharedPointer<Router> RouterPtr_t;

#endif    // ROUTER_H

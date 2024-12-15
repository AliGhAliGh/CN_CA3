#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include "src/Port/Port.h"

#include <QObject>

class Router : public Node
{
public:
    explicit Router(uint8_t id, QObject *parent = nullptr);

    PortPtr_t getPort(int id);

    PortPtr_t getFreePort();

    PortPtr_t setBGP();

    void      setBroken(bool isBroken = true);

private:
    uint8_t            m_id;
    QVector<PortPtr_t> m_ports;
    /*    1
     * 3     2
     *    4
     */
};

typedef QSharedPointer<Router> RouterPtr_t;

#endif    // ROUTER_H

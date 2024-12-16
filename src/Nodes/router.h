#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include "src/Port/Port.h"

#include <QObject>
#include <QVector>

class Router : public Node
{
    Q_OBJECT

public:
    explicit Router(uint8_t id, QObject *parent = nullptr);

    PortPtr_t getPort(int id);    // دریافت یک پورت خاص
    PortPtr_t getFreePort();      // دریافت یک پورت آزاد
    PortPtr_t setBGP();
    void      setBroken(bool isBroken = true);

Q_SIGNALS:
    void routerStatusChanged(uint8_t routerId, bool isBroken);

private:
    QVector<PortPtr_t> m_ports; // پورت‌های روتر
    bool               m_isBroken;
};

typedef QSharedPointer<Router> RouterPtr_t;

#endif // ROUTER_H

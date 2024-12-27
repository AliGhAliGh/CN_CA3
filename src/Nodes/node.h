#ifndef NODE_H
#define NODE_H

#include "src/IP/IP.h"
#include "src/IP/macaddress.h"

#include <QObject>
#include <QSharedPointer>
#include <QThread>

class Node : public QThread
{
    Q_OBJECT

public:
    explicit Node(uint8_t id, QObject *parent = nullptr);
    virtual ~Node() override = default;
    void        setMac(MacAddress *mac);
    AbstractIP *getIp();
    MacAddress *getMac();
    uint8_t getId();

Q_SIGNALS:
    void packetSent(uint8_t nodeId);
    void packetReceived(uint8_t nodeId);

protected Q_SLOTS:
    virtual void tick(unsigned long long data);

protected:
    AbstractIP *m_ip;
    MacAddress *m_mac;

private:
    uint8_t m_id;
};

typedef QSharedPointer<Node> NodePtr_t;

#endif    // NODE_H

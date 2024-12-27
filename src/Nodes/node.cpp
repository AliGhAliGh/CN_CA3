#include "node.h"

#include "src/EventsCoordinator/EventsCoordinator.h"

Node::Node(uint8_t id, QObject *parent) :
    QThread {parent},
    m_id {id}
{
    connect(EventsCoordinator::instance(), &EventsCoordinator::global_tick, this, &Node::tick);
}

void
Node::setMac(MacAddress *mac)
{
    m_mac = mac;
}

AbstractIP *
Node::getIp()
{
    return m_ip;
}

MacAddress *
Node::getMac()
{
    return m_mac;
}

uint8_t
Node::getId()
{
    return m_id;
}

void
Node::tick(unsigned long long data)
{}

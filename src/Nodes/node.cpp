#include "node.h"

#include "src/EventsCoordinator/EventsCoordinator.h"

Node::Node(uint8_t id, QObject *parent) :
    QThread {parent},
    m_id {id}
{
    connect(EventsCoordinator::instance(), &EventsCoordinator::global_tick, this, &Node::tick);
}

uint8_t
Node::getId()
{
    return m_id;
}

void
Node::tick(unsigned long long data)
{}

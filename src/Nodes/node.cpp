#include "node.h"

Node::Node(uint8_t id, QObject *parent) :
    QThread {parent},
    m_id {id}
{
}

uint8_t
Node::getId()
{
    return m_id;
}

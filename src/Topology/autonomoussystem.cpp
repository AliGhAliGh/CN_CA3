#include "autonomoussystem.h"

#include "src/IP/macaddressgenerator.h"

AutonomousSystem::AutonomousSystem(uint8_t id, QObject *parent) :
    QObject {parent}
{
    m_id = id;
}

void
AutonomousSystem::SetRouters(QVector<RouterPtr_t> routers)
{
    for(int i = 0; i < routers.size(); ++i)
    {
        routers[i]->setMac(MacAddressGenerator::generate());
        m_nodes.append(routers[i]);
    }
}

uint8_t
AutonomousSystem::getId()
{
    return m_id;
}

RouterPtr_t
AutonomousSystem::GetRouter(uint8_t id)
{
    for(NodePtr_t &node : m_nodes)
        if(node->getId() == id) return node.dynamicCast<Router>();
    return nullptr;
}

void
AutonomousSystem::test()
{
    // m_nodes[0].
}

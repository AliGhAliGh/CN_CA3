#include "autonomoussystem.h"

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
        m_nodes.append(routers[i]);
    }
}

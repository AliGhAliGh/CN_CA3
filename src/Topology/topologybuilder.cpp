#include "topologybuilder.h"

#include <QJsonArray>
#include <QJsonObject>

QList<AutonomousSystem> TopologyBuilder::m_autonomousSystems;
PortBindingManager      TopologyBuilder::m_binder;

TopologyBuilder::TopologyBuilder(QObject *parent) :
    QObject {parent}
{}

void
TopologyBuilder::setRouters(AutonomousSystem &as, const QJsonObject data)
{
    auto               topologies = data["topology_type"].toArray();
    QList<RouterPtr_t> routers;
    for(int i = 0; i < topologies.size(); ++i)
    {
        routers.clear();
        int scale = data["scale"].toInt();
        if(scale < 1) throw std::invalid_argument("min scale for topology is 1!");
        bool isTuros = topologies[i].toString() == "Torus";
        if(topologies[i].toString() == "Mesh" || isTuros)
        {
            for(int row = 0; row < scale; ++row)
                for(int col = 0; col < scale; ++col)
                {
                    auto router = RouterPtr_t(new Router(routers.size() + 1));
                    routers.append(router);
                    if(col > 0)
                        m_binder.bind(router->getPort(3),
                                      routers[row * scale + col - 1]->getPort(2));

                    if(row > 0)
                        m_binder.bind(router->getPort(1),
                                      routers[(row - 1) * scale + col]->getPort(4));

                    if(isTuros)
                    {
                        if(col == scale - 1)
                            m_binder.bind(router->getPort(2), routers[row * scale]->getPort(3));
                        if(row == scale - 1)
                            m_binder.bind(router->getPort(4), routers[col]->getPort(1));
                    }
                }
        }
        else if(topologies[i].toString() == "RingStar")
        {
            if(scale > 4) throw std::invalid_argument("max scale for RingStar is 4!");
            for(int i = 0; i < scale; ++i)
            {
                auto router1 = RouterPtr_t(new Router(routers.size() + 1));
                routers.append(router1);
                auto router2 = RouterPtr_t(new Router(routers.size() + 1));
                routers.append(router2);
                m_binder.bind(router1->getPort(2), router2->getPort(3));
                if(i > 0) m_binder.bind(router1->getPort(3), routers[(i - 1) * 2 + 1]->getPort(2));
                if(i == scale - 1) m_binder.bind(router2->getPort(2), routers[0]->getPort(3));
            }
            for(int i = 0; i < scale; ++i)
            {
                auto centeral = RouterPtr_t(new Router(routers.size() + 1));
                routers.append(centeral);
                m_binder.bind(centeral->getPort(i), routers[2 * i]->getPort(4));
            }
        }
        as.SetRouters(routers);
    }
}

void
TopologyBuilder::Build_AS(QJsonObject data)
{
    auto as = AutonomousSystem(data["id"].toInt());
    setRouters(as, data);
    m_autonomousSystems.append(as);
}

#include "topologybuilder.h"

#include "src/Nodes/pc.h"

#include <QJsonArray>
#include <QJsonObject>

QList<ASPtr_t>     TopologyBuilder::m_autonomousSystems;
PortBindingManager TopologyBuilder::m_binder;

TopologyBuilder::TopologyBuilder(QObject *parent) :
    QObject {parent}
{}

void
TopologyBuilder::setRouters(AutonomousSystem &as, const QJsonObject &data)
{
    auto               topologies = data["topology_type"].toArray();
    auto               brokens    = data["broken_routers"].toArray();
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
                    auto id     = routers.size() + 1;
                    auto router = RouterPtr_t(new Router(id));
                    routers.append(router);

                    if(brokens.contains(id)) router->setBroken();

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
TopologyBuilder::setPCs(AutonomousSystem &as, const QJsonObject &data)
{
    auto             users = data["gateways"].toArray();
    QVector<PCPtr_t> pcs;
    for(int i = 0; i < users.size(); ++i)
    {
        auto obj      = users[i].toObject();
        auto gateway  = as.GetRouter(obj["node"].toInt())->getFreePort();
        auto user_ids = obj["users"].toArray();
        for(int j = 0; j < user_ids.size(); ++j)
        {
            auto pc = PCPtr_t(new PC(user_ids[j].toInt()));
            pcs.append(pc);
            m_binder.bind(pc->getPort(), gateway);
        }
    }
}

void
TopologyBuilder::connectASs(AutonomousSystem &as1, AutonomousSystem &as2, const QJsonObject &data)
{
    auto array = data["gateway_pairs"].toArray();
    for(int i = 0; i < array.size(); ++i)
    {
        auto obj     = array[i].toObject();
        auto router1 = as1.GetRouter(obj["gateway"].toInt());
        auto router2 = as2.GetRouter(obj["connect_to"].toInt());
        m_binder.bind(router1->setBGP(), router2->setBGP());
    }
}

void
TopologyBuilder::Build_AS(QJsonObject data)
{
    auto as = ASPtr_t(new AutonomousSystem(data["id"].toInt()));
    setRouters(*as, data);
    setPCs(*as, data);
    if(!data["connect_to_as"].isNull())
    {
        auto array = data["connect_to_as"].toArray();
        for(int i = 0; i < array.size(); ++i)
            for(ASPtr_t &as2 : m_autonomousSystems)
                if(as2->getId() == array[i].toObject()["id"].toInt())
                    connectASs(*as, *as2, array[i].toObject());
    }

    m_autonomousSystems.append(as);
}

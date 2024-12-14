#include "topologybuilder.h"

#include <QJsonObject>

QList<AutonomousSystem> TopologyBuilder::m_autonomousSystems;

TopologyBuilder::TopologyBuilder(QObject *parent) :
    QObject {parent}
{}

void
TopologyBuilder::Build_AS(QJsonObject data)
{
    auto as = AutonomousSystem(data["id"].toInt());
    //todo
    m_autonomousSystems.append(as);
}

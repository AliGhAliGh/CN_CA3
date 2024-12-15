#ifndef TOPOLOGYBUILDER_H
#define TOPOLOGYBUILDER_H

#include "src/Port/PortBindingManager.h"
#include "src/Topology/autonomoussystem.h"

#include <QObject>

enum class Topology
{
    Mesh,
    Torus,
    RingStar
};

class TopologyBuilder : public QObject
{
    Q_OBJECT

public:
    explicit TopologyBuilder(QObject *parent = nullptr);

    static void Build_AS(QJsonObject data);

Q_SIGNALS:

private:
    static void setRouters(AutonomousSystem &as, const QJsonObject &data);
    static void setPCs(AutonomousSystem &as, const QJsonObject &data);
    static void connectASs(AutonomousSystem &as1, AutonomousSystem &as2, const QJsonObject &data);

    static QList<ASPtr_t>     m_autonomousSystems;
    static PortBindingManager m_binder;
};

#endif    // TOPOLOGYBUILDER_H

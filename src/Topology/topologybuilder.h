#ifndef TOPOLOGYBUILDER_H
#define TOPOLOGYBUILDER_H

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
};

#endif    // TOPOLOGYBUILDER_H

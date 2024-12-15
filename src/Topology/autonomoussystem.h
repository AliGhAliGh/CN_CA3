#ifndef AUTONOMOUSSYSTEM_H
#define AUTONOMOUSSYSTEM_H

#include <src/Nodes/node.h>
#include <src/Nodes/router.h>

#include <QObject>

class AutonomousSystem : public QObject
{
    Q_OBJECT

public:
    explicit AutonomousSystem(uint8_t id, QObject *parent = nullptr);

    void SetRouters(QVector<RouterPtr_t> routers);

Q_SIGNALS:

private:
    QList<NodePtr_t> m_nodes;
    uint8_t     m_id;
};

#endif    // AUTONOMOUSSYSTEM_H

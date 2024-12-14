#ifndef AUTONOMOUSSYSTEM_H
#define AUTONOMOUSSYSTEM_H

#include <src/node.h>

#include <QObject>

class AutonomousSystem : public QObject
{
    Q_OBJECT

public:
    explicit AutonomousSystem(uint8_t id, QObject *parent = nullptr);

Q_SIGNALS:

private:
    QList<Node> m_nodes;
    uint8_t     m_id;
};

#endif    // AUTONOMOUSSYSTEM_H

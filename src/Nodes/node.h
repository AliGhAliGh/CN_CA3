#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QThread>

class Node : public QThread
{
public:
    explicit Node(uint8_t id, QObject *parent = nullptr);

    uint8_t getId();

private:
    uint8_t m_id;
};

typedef QSharedPointer<Node> NodePtr_t;

#endif    // NODE_H

#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QThread>

class Node : public QThread
{
public:
    explicit Node(QObject *parent = nullptr);
};

typedef QSharedPointer<Node> NodePtr_t;

#endif    // NODE_H

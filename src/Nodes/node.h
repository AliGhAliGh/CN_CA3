#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>

class Node : public QThread
{
    Q_OBJECT

public:
    explicit Node(uint8_t id, QObject *parent = nullptr);
    virtual ~Node() override = default;

    uint8_t getId();

Q_SIGNALS:
    void packetSent(uint8_t nodeId);
    void packetReceived(uint8_t nodeId);
private:
    uint8_t m_id; // شناسه گره
};

typedef QSharedPointer<Node> NodePtr_t;

#endif // NODE_H

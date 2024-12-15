#include "PortBindingManager.h"

#include "qdebug.h"

PortBindingManager::PortBindingManager(QObject *parent) :
    QObject {parent}
{}

void
PortBindingManager::bind(const PortPtr_t &port1, const PortPtr_t &port2)
{
    bindHalf(port1, port2);
    bindHalf(port2, port1);
}

bool
PortBindingManager::unbind(const PortPtr_t &port1, const PortPtr_t &port2)
{
    if(unbindHalf(port1, port2))
        if(unbindHalf(port2, port1)) return true;
    return false;
}

void
PortBindingManager::bindHalf(PortPtr_t from, PortPtr_t to)
{
    connect(from.get(), &Port::packetSent, to.get(), &Port::receivePacket);
    if(bindings.contains(from))
    {
        auto list = bindings[from];
        if(list.contains(to))
            qDebug() << "Port Already Binded!";
        else if(list.size() > 0 && to->isRouterPort())
            qDebug() << "Bad Router Binding!";
        else
        {
            list.append(to);
            to->IsFree = from->IsFree = false;
        }
    }
    else
        bindings[from] = *new QList<PortPtr_t>({to});
}

bool
PortBindingManager::unbindHalf(PortPtr_t from, PortPtr_t to)
{
    if(bindings.contains(from) && bindings[from].contains(to))
    {
        disconnect(from.get(), &Port::packetSent, to.get(), &Port::receivePacket);
        bindings[from].removeOne(to);
        to->IsFree = from->IsFree = true;
        return true;
    }
    qDebug() << "Binding Not Exist!";
    return false;
}

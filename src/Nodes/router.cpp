#include "router.h"

Router::Router(uint8_t id, QObject *parent) :
    Node {id, parent}
{}

PortPtr_t
Router::getPort(int id)
{}

PortPtr_t
Router::getFreePort()
{}

PortPtr_t
Router::setBGP()
{}

void
Router::setBroken(bool isBroken)
{}

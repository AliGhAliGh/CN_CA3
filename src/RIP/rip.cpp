#include "rip.h"
#include <QDebug>

RIP::RIP(Router* router, QObject* parent)
    : QObject(parent), m_router(router) {}

void RIP::sendRoutingTable() {
    for (auto& port : m_router->getPorts()) {
        if (!port->isFree() && !port->isBroken()) {
            QVector<RoutingEntry> tableToSend = m_routingTable;

            // افزودن متریک به جدول مسیریابی قبل از ارسال
            for (auto& entry : tableToSend) {
                entry.metric += 1; // هزینه ارسال به همسایه
            }

            qDebug() << "Router" << m_router->getId() << ": Sending routing table to"
                     << port->getConnectedRouterId();
            port->sendPacket(PacketPtr_t(Packet::RoutingPacket(m_router->getId(), tableToSend)));
        }
    }
}

void RIP::receiveRoutingTable(const QVector<RoutingEntry>& receivedTable, uint8_t fromRouter) {
    qDebug() << "Router" << m_router->getId() << ": Received routing table from" << fromRouter;
    updateRoutingTable(receivedTable, fromRouter);
}

void RIP::updateRoutingTable(const QVector<RoutingEntry>& receivedTable, uint8_t fromRouter) {
    bool updated = false;

    for (const auto& entry : receivedTable) {
        // محاسبه متریک جدید
        int newMetric = entry.metric + m_neighbors[fromRouter];

        // بررسی وجود مسیر در جدول
        auto it = std::find_if(m_routingTable.begin(), m_routingTable.end(), [&entry](const RoutingEntry& e) {
            return e.destination == entry.destination;
        });

        if (it == m_routingTable.end()) {
            // افزودن مسیر جدید
            m_routingTable.append({entry.destination, fromRouter, newMetric});
            updated = true;
        } else if (newMetric < it->metric) {
            // بروزرسانی مسیر با متریک بهتر
            it->nextHop = fromRouter;
            it->metric = newMetric;
            updated = true;
        }
    }

    if (updated) {
        Q_EMIT routingTableUpdated(m_router->getId(), m_routingTable);
    }
}

QVector<RoutingEntry> RIP::getRoutingTable() const {
    return m_routingTable;
}

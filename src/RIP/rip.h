#ifndef RIP_H
#define RIP_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../Nodes/router.h"

// ساختار جدول مسیریابی
struct RoutingEntry {
    uint8_t destination;
    uint8_t nextHop;
    int metric;
};

class RIP : public QObject {
    Q_OBJECT

public:
    explicit RIP(Router* router, QObject* parent = nullptr);

    // ارسال جدول مسیریابی به همسایگان
    void sendRoutingTable();

    // دریافت جدول مسیریابی از یک روتر دیگر
    void receiveRoutingTable(const QVector<RoutingEntry>& receivedTable, uint8_t fromRouter);

    // بروزرسانی جدول مسیریابی
    void updateRoutingTable(const QVector<RoutingEntry>& receivedTable, uint8_t fromRouter);

    // گرفتن جدول مسیریابی برای دیباگ یا نمایش
    QVector<RoutingEntry> getRoutingTable() const;

Q_SIGNALS:
    // سیگنالی برای ارسال جدول مسیریابی
    void routingTableUpdated(uint8_t routerId, const QVector<RoutingEntry>& table);

private:
    Router* m_router;                     // اشاره به روتر
    QVector<RoutingEntry> m_routingTable; // جدول مسیریابی
    QMap<uint8_t, int> m_neighbors;       // لیست همسایگان با هزینه‌ها
};

#endif // RIP_H

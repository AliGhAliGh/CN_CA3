#ifndef MACADDRESSGENERATOR_H
#define MACADDRESSGENERATOR_H

#include "macaddress.h"

#include <QObject>

class MacAddressGenerator : public QObject
{
    Q_OBJECT

public:
    explicit MacAddressGenerator(QObject *parent = nullptr);

    static MacAddress* generate();

    static MacAddress* broadcastMac();

private:
    static QVector<MacAddress*> m_generated;
};

#endif    // MACADDRESSGENERATOR_H

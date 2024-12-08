#ifndef MACADDRESSGENERATOR_H
#define MACADDRESSGENERATOR_H

#include <QObject>

class MacAddressGenerator : public QObject
{
    Q_OBJECT

public:
    explicit MacAddressGenerator(QObject *parent = nullptr);

    static char *generate();

Q_SIGNALS:
};

#endif    // MACADDRESSGENERATOR_H

#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <bitset>

#include <QObject>

class MacAddress : public QObject
{
    Q_OBJECT

public:
    explicit MacAddress(char address[12], QObject *parent = nullptr);

    std::string to_string();

Q_SIGNALS:

private:
    std::bitset<48> address;
};

#endif    // MACADDRESS_H

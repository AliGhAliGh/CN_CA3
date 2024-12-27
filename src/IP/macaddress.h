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

    bool
    operator==(const MacAddress &other) const
    {
        return m_address == other.m_address;
    }

Q_SIGNALS:

private:
    std::bitset<48> m_address;
};

#endif    // MACADDRESS_H

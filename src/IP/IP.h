#ifndef IP_H
#define IP_H

#include "Globals.h"

#include <bitset>

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QTextStream>

class AbstractIP : public QObject
{
    Q_OBJECT

public:
    explicit AbstractIP(QObject *parent = nullptr);
    virtual std::string to_string() const = 0;

Q_SIGNALS:

protected:
};

typedef QSharedPointer<AbstractIP> IPPtr_t;

template <>
class UT::IP<UT::IPVersion::IPv4> : public AbstractIP
{
public:    // constructors
    explicit IP(QObject *parent = nullptr);
    explicit IP(const QString &ipString, QObject *parent = nullptr);
    explicit IP(uint32_t ipValue, QObject *parent = nullptr);
    explicit IP(std::bitset<32> ipValue, QObject *parent = nullptr);
    ~IP() override;
    std::bitset<32> getData();

public:    // methods

public:    // operators
    bool
    operator==(const IP<UT::IPVersion::IPv4> &other) const
    {
        return m_value.to_string() == other.m_value.to_string();
    }

    std::string to_string() const override;

private:    // methods

private:
    std::bitset<32> m_value;
};

template <>
class UT::IP<UT::IPVersion::IPv6> : public AbstractIP
{
public:    // constructors
    explicit IP(QObject *parent = nullptr);
    explicit IP(const QString &ipString, QObject *parent = nullptr);
    // explicit IP(uint64_t ipValue, QObject *parent = nullptr);
    ~IP() override;

public:    // methods

public:    // operators
    bool
    operator==(const IP<UT::IPVersion::IPv6> &other) const
    {
        return value.to_string() == other.value.to_string();
    }

    std::string to_string() const override;

private:

private:
    std::bitset<128> value;
};

#endif    // IP_H

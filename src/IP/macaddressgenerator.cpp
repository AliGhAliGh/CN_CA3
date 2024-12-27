#include "macaddressgenerator.h"

#include "src/IP/macaddress.h"

QVector<MacAddress *> MacAddressGenerator::m_generated;

MacAddressGenerator::MacAddressGenerator(QObject *parent) :
    QObject {parent}
{
    std::srand(810'100'201);
}

MacAddress *
MacAddressGenerator::generate()
{
    char *res = new char[12];
    res[0]    = 1;
    for(int i = 1; i < 12; ++i)
        res[i] = std::rand() % 16;
    auto result = new MacAddress(res);
    for(auto &mac : m_generated)
        if(*mac == *result) return generate();
    m_generated.append(result);
    return result;
}

MacAddress *
MacAddressGenerator::broadcastMac()
{
    char *res = new char[12];
    for(int i = 0; i < 12; ++i)
        res[i] = 0;
    return new MacAddress(res);
}

#include "macaddressgenerator.h"

MacAddressGenerator::MacAddressGenerator(QObject *parent) :
    QObject {parent}
{
    std::srand(810'100'201);
}

char *
MacAddressGenerator::generate()
{
    char *res = new char[12];
    for(int i = 0; i < 12; ++i)
        res[i] = std::rand() % 16;
    return res;
}

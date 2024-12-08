#include "macaddress.h"

#include <iostream>
#include <sstream>

MacAddress::MacAddress(char address[12], QObject *parent) :
    QObject {parent}
{
    for(int i = 0; i < 12; ++i)
    {
        char c = address[i];
        for(int j = 3; j >= 0; --j)
        {
            if(c & 0b0001) this->address.set(47 - 4 * i - j);
            c >>= 1;
        }
    }
}

std::string
MacAddress::to_string()
{
    auto        divider = std::bitset<48>(15);
    std::string res     = "";
    for(auto i = 0; i < 12; i++)
    {
        std::stringstream temp;
        temp << std::hex << std::uppercase << ((address >> (4 * i)) & divider).to_ulong();
        res = temp.str() + res;
        if(i % 2 == 1 && i != 11) res = ':' + res;
    }
    return res;
}

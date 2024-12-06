QT     += core
CONFIG += lrelease
CONFIG += no_keywords
CONFIG += c++20

INCLUDEPATH += $$PWD\Globals

SOURCES += \
    $$PWD/DHCPServer/DHCPServer.cpp \
    $$PWD/EventsCoordinator/EventsCoordinator.cpp \
    $$PWD/IP/IP.cpp \
    $$PWD/IP/macaddress.cpp \
    $$PWD/IP/macaddressgenerator.cpp \
    $$PWD/Packets/packet.cpp \
    $$PWD/PortBindingManager/PortBindingManager.cpp \
    $$PWD/Port/Port.cpp \
    $$PWD/Packets/Packet.cpp \
    $$PWD/main.cpp

HEADERS += \
    $$PWD/DHCPServer/DHCPServer.h \
    $$PWD/EventsCoordinator/EventsCoordinator.h \
    $$PWD/Globals/Globals.h \
    $$PWD/IP/IP.h \
    $$PWD/IP/macaddress.h \
    $$PWD/IP/macaddressgenerator.h \
    $$PWD/Packets/packet.h \
    $$PWD/PortBindingManager/PortBindingManager.h \
    $$PWD/Port/Port.h \
    $$PWD/Packets/Packet.h \

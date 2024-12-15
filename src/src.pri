QT     += core
CONFIG += lrelease
CONFIG += no_keywords
CONFIG += c++20

INCLUDEPATH += $$PWD\Globals
# INCLUDEPATH += C:/boost/boost_1_82_0/

# LIBS += -LC:/boost/boost_1_82_0/libs/

SOURCES += \
    # $$PWD/DHCPServer/DHCPServer.cpp \
    $$PWD/EventsCoordinator/EventsCoordinator.cpp \
    $$PWD/EventsCoordinator/datagenerator.cpp \
    $$PWD/IP/IP.cpp \
    $$PWD/IP/macaddress.cpp \
    $$PWD/IP/macaddressgenerator.cpp \
    $$PWD/Nodes/router.cpp \
    $$PWD/Packets/packet.cpp \
    $$PWD/PortBindingManager/PortBindingManager.cpp \
    $$PWD/Port/Port.cpp \
    $$PWD/Topology/autonomoussystem.cpp \
    $$PWD/Topology/topologybuilder.cpp \
    $$PWD/main.cpp \
    $$PWD/Nodes/node.cpp

HEADERS += \
    # $$PWD/DHCPServer/DHCPServer.h \
    $$PWD/EventsCoordinator/EventsCoordinator.h \
    $$PWD/EventsCoordinator/datagenerator.h \
    $$PWD/Globals/Globals.h \
    $$PWD/IP/IP.h \
    $$PWD/IP/macaddress.h \
    $$PWD/IP/macaddressgenerator.h \
    $$PWD/Nodes/router.h \
    $$PWD/Packets/packet.h \
    $$PWD/PortBindingManager/PortBindingManager.h \
    $$PWD/Port/Port.h \
    $$PWD/Topology/autonomoussystem.h \
    $$PWD/Topology/topologybuilder.h \
    $$PWD/Nodes/node.h

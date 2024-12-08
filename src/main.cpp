#include "EventsCoordinator/EventsCoordinator.h"
#include "src/IP/macaddress.h"
#include "src/IP/macaddressgenerator.h"

#include <iostream>

#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void
readJson()
{
    QString val;
    QFile   file;
    file.setFileName("assets/config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d     = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject   sett2 = d.object();
    QJsonValue    value = sett2.value(QString("appName"));
    qWarning() << value;
    QJsonObject item   = value.toObject();
    // qWarning() << tr("QJsonObject of description: ") << item;

    /* in case of string value get value and convert into string*/
    // qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    QJsonValue  subobj = item["description"];
    qWarning() << subobj.toString();

    /* in case of array get array and convert into string*/
    // qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    QJsonArray test = item["imp"].toArray();
    qWarning() << test[1].toString();
}

int
main(int argv, char* argc[])
{
    QCoreApplication app(argv, argc);
    EventsCoordinator::init(1'000);
    MacAddress a(MacAddressGenerator::generate());
    MacAddress b(MacAddressGenerator::generate());
    std::cout << a.to_string() << std::endl;
    std::cout << b.to_string() << std::endl;
    return app.exec();
}

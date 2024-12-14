#include "EventsCoordinator/EventsCoordinator.h"
#include "src/Topology/topologybuilder.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void
applyConfig()
{
    QString val;
    QFile   file;
    file.setFileName("assets/config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d     = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject   json  = d.object();
    QJsonArray    AS    = json.value(QString("Autonomous_systems")).toArray();
    for(int i = 0; i < AS.size(); ++i)
        TopologyBuilder::Build_AS(AS[i].toObject());
}

int
main(int argv, char* argc[])
{
    QCoreApplication app(argv, argc);
    EventsCoordinator::init(1'000);
    applyConfig();
    return app.exec();
}

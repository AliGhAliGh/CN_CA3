#ifndef EVENTSCOORDINATOR_H
#define EVENTSCOORDINATOR_H

#include "src/EventsCoordinator/datagenerator.h"

#include <QObject>
#include <QThread>

class EventsCoordinator : public QThread
{
    Q_OBJECT
    typedef std::chrono::milliseconds Millis;

public:    // constructors
    ~EventsCoordinator() override                     = default;
    EventsCoordinator(const EventsCoordinator &other) = delete;

public:    // methods
    static void               init(int millis);
    static EventsCoordinator *instance();

public:    // getter and setters
Q_SIGNALS:
    void global_tick(unsigned long long num);

private Q_SLOTS:
    void clock();

public Q_SLOTS:

private:
    explicit EventsCoordinator(QThread *parent = nullptr);

private:    // members
    static EventsCoordinator *instancePtr;
    static std::mutex         mtx;
    static unsigned long long num;
    static DataGenerator      dataGenerator;
};

#endif    // EVENTSCOORDINATOR_H

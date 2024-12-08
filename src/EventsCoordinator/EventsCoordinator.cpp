#include "EventsCoordinator.h"

#include <iostream>
#include <mutex>

#include <QTimer>

EventsCoordinator *EventsCoordinator::instancePtr = nullptr;
std::mutex         EventsCoordinator::mtx;
unsigned long long EventsCoordinator::num;
DataGenerator      EventsCoordinator::dataGenerator(Distribution::Poisson);

EventsCoordinator::EventsCoordinator(QThread *parent) :
    QThread {parent}
{}

void
EventsCoordinator::init(int millis)
{
    QTimer *timer = new QTimer();
    instance();
    connect(timer, &QTimer::timeout, instance(), &EventsCoordinator::clock);
    timer->start(Millis(millis));
}

void
EventsCoordinator::clock()
{
    auto data = EventsCoordinator::dataGenerator.generate(num++);
    std::cout << "call: " << data << std::endl;
    Q_EMIT global_tick(data);
}

EventsCoordinator *
EventsCoordinator::instance()
{
    if(instancePtr == nullptr)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if(instancePtr == nullptr) instancePtr = new EventsCoordinator();
    }
    return instancePtr;
}

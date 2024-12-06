#include "EventsCoordinator.h"

#include <mutex>

#include <QTimer>

EventsCoordinator *EventsCoordinator::instancePtr = nullptr;
std::mutex         EventsCoordinator::mtx;

EventsCoordinator::EventsCoordinator(QThread *parent) :
    QThread {parent}
{}

void
EventsCoordinator::init(Millis millis)
{
    QTimer *timer = new QTimer();
    instance();
    connect(timer, &QTimer::timeout, instance(), &EventsCoordinator::clock);
    timer->start(millis);
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

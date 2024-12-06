#ifndef EVENTSCOORDINATOR_H
#define EVENTSCOORDINATOR_H

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
    static void               init(Millis millis);
    static EventsCoordinator *instance();

public:    // getter and setters
Q_SIGNALS:
    void clock();

public Q_SLOTS:

private Q_SLOTS:

private:
    explicit EventsCoordinator(QThread *parent = nullptr);

private:    // members
    static EventsCoordinator *instancePtr;
    static std::mutex         mtx;
};

#endif    // EVENTSCOORDINATOR_H

#ifndef WALKTHREAD_H
#define WALKTHREAD_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QObject>
#include <QThread>
#include <QQueue>

#define FOREVER 3600


enum tasks {
    TSK_STEP_FORWARD,
    TSK_STEP_BACKWARD,
    TSK_TURN_LEFT,
    TSK_TURN_RIGHT,
    TSK_STOP
};

struct stCommands {
    tasks m_command;
    QList<int>  params;
};

class walkThread : public QThread
{
    Q_OBJECT
public:
    explicit walkThread(QObject *parent = nullptr);
    void setSpeed      (int speed);
    void pushTask      (tasks task);


private:
    void stepForward   ();
    void stepBackward  ();
    void turnLeft      ();
    void turnRight     ();
    void stop          ();
    void run           ();

private:
    QDBusInterface *m_pEnginesIface;
    int             m_speed=2;
    QQueue<tasks>   m_tasks;

signals:

};

#endif // WALKTHREAD_H

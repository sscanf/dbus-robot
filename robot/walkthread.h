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
    enum direction {
        DIR_ERROR=-1,
        DIR_FORWARDING,
        DIR_TURNING_LEFT,
        DIR_TURNING_RIGHT,
        DIR_BACKWARDING,
        DIR_STOPPED
    };

    explicit walkThread(QDBusConnection connection, QObject *parent = nullptr);
    void       setDualSpeed  (int left, int right);
    void       setSpeed      (int speed);
    int        getSpeed      (void);
    void       pushTask      (tasks task);
    direction  getDirection  ();
    QList<QVariant> getCollisions();
    void       terminate();
    void       turn (int speed);


private:
    void stepForward   ();
    void stepBackward  ();
    void turnLeft      ();
    void turnRight     ();
    void stop          ();
    void run           ();

private:
    QDBusConnection m_connection;
    QDBusInterface *m_pEnginesIface;
    QDBusInterface *m_pSensorsIface;
    int             m_speed=2;
    QQueue<tasks>   m_tasks;

private slots:
    void onEnginesError (int err);

signals:
    void error (int);

};

#endif // WALKTHREAD_H

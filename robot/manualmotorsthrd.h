#ifndef MANUALMOTORSTHRD_H
#define MANUALMOTORSTHRD_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QThread>

#define MAX_SPEED 30

class manualMotorsThrd : public QThread
{
    Q_OBJECT
public:
    explicit manualMotorsThrd(QDBusConnection connection, QThread *parent = nullptr);
    void run();
    void terminate();

private:
    double map(double x, double in_min, double in_max, double out_min, double out_max);
    void setSpeed();

private:
    QDBusInterface *m_pEnginesIface;
    int             m_valL=0;
    int             m_valR=0;
    int             m_speed=0;

private slots:
    void onAxisLeftX (double);
    void onAxisLeftY (double);

};

#endif // MANUALMOTORSTHRD_H

#ifndef MANUALCAMERATHRD_H
#define MANUALCAMERATHRD_H

#include <QDBusConnection>
#include <QDBusInterface>
#include <QThread>

class manualCameraThrd : public QThread
{
    Q_OBJECT
public:
    explicit manualCameraThrd(QDBusConnection connection, QThread *parent = nullptr);
    void run();
    void terminate();

private:
    double map(double x, double in_min, double in_max, double out_min, double out_max);


private:
    QDBusInterface *m_pCameraIface;
    bool m_processing=false;

private slots:
    void onAxisRightX (double);
    void onAxisRightY (double);

signals:

};

#endif // MANUALCAMERATHRD_H

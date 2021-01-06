#ifndef ZOPOSIRCAM_H
#define ZOPOSIRCAM_H

#include <QObject>
#include <QPoint>
#include <zoi2c.h>

class ZOPosIRCam : public QObject
{
    Q_OBJECT
public:
    explicit ZOPosIRCam(QObject *parent = nullptr);

public slots:
    void process();

private:
    void cameraInit();

private:
    int   m_IRsensorAddress;
    char  m_slaveAddress;
    zoi2c m_zoi2c;

signals:
    void detection(QPoint source1, QPoint source2, QPoint source3, QPoint source4);


public slots:
};

#endif // ZOPOSIRCAM_H

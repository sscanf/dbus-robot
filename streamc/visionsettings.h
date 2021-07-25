#ifndef VISIONSETTINGS_H
#define VISIONSETTINGS_H

#include <QDialog>
#include <QTcpSocket>
#include <QImage>
#include <QTimer>
#include <QColor>
#include "../common/robot.h"

#define ILOW_H  100
#define ILOW_S  100
#define ILOW_V  100
#define IHIGH_H 10
#define IHIGH_S 255
#define IHIGH_V 255

namespace Ui {
class visionSettings;
}

class visionSettings : public QDialog
{
    Q_OBJECT

public:
    explicit visionSettings(QWidget *parent = nullptr);
    ~visionSettings();

private:
    void sendData (void);

private:
    Ui::visionSettings *ui;
    QTcpSocket         *m_pSocket;
    quint64             m_totalBytes;
    QByteArray          m_arrImage;
    QTimer             *m_pTimer;
    int                 m_iLowH;
    int                 m_iHighH;
    int                 m_iLowS;
    int                 m_iHighS;
    int                 m_iLowV;
    int                 m_iHighV;
    QColor              m_color;

private slots:
    void on_connected();
    void on_readyRead();
    void on_disconnected();
    void on_timeout();
    void on_lowhChanged(int value);
    void on_lowsChanged(int value);
    void on_lowvChanged(int value);
    void on_highhChanged(int value);
    void on_highsChanged(int value);
    void on_highvChanged(int value);
    void on_highChanged(int);
    void on_lowChanged(int);
    void on_cameraChanged(int);
};
#endif // VISIONSETTINGS_H

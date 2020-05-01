#ifndef IMX6IO_H
#define IMX6IO_H

#include <QObject>
#include "qsoc.h"

/**
MXM3_17   //GPIO6
MXM3_1    //GPIO36
MXM3_3    //GPIO37
MXM3_5    //GPIO38
MXM3_7    //GPIO39
**/

class imx6io : public QObject
{
    Q_OBJECT
    Q_ENUMS(IODirection)
    Q_ENUMS(IOValue)
//    Q_DISABLE_COPY(imx6io)


public:
    imx6io(QObject *parent = nullptr);
    ~imx6io();

    enum IODirection {
        Output,
        Input
    };

    enum IOValue {
        VALUE_ERROR = -1,
        Low,
        High
    };

public:
    QString getName     ();
    void    setName     (QString name);
    void    setDirection(IODirection dir);
    void    setValue    (IOValue val);
    IOValue getValue    ();

signals:
    void pressed();
    void released();
    void valueChanged(IOValue value);

private:
    void UpdateIO();
    static int callbackButton(void *ptr);

private:
    QSoc           m_soc;
    QString        m_strName;
    gpio_direction m_direction;
    gpio_level     m_value;

private slots:
    void onTimeout();

};
#endif // IMX6IO_H

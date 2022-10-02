#ifndef QSOC_H
#define QSOC_H

#include <libsoc_gpio.h>
#include <libsoc_board.h>
#include <QObject>
#include <QHash>

class QSoc : public QObject {
    Q_OBJECT

public:
    explicit QSoc(QObject *parent = nullptr);
    ~QSoc();

    int        addNewGPIO(QString strName, gpio_direction direction);
    int        setLevel(QString strName, gpio_level level);
    gpio_level level(QString strName);
    int        enableInterrupt(QString strName, gpio_edge edge, int (*callback_fn)(void *), void *ptr);
    int        setDirection(QString strName, gpio_direction dir);
    void       disableInterrupt(QString strName);

protected:
    QHash<QString, gpio *> m_gpios;
    board_config *         m_pConfig;
    QHash<QString, gpio *> m_pGpioInterrupts;

signals:

public slots:
};

#endif // QSOC_H

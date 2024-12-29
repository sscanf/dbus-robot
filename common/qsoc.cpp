#include "qsoc.h"
#include <QtDebug>

QSoc::QSoc(QObject *parent)
    : QObject(parent) {
    m_pConfig = libsoc_board_init();
    qDebug() << m_pConfig;
}

QSoc::~QSoc() {
    foreach (gpio *pGpio, m_gpios) { //
        libsoc_gpio_free(pGpio);
    }
}

int QSoc::addNewGPIO(QString strName, gpio_direction direction) {
    gpio *pGpio = nullptr;
    int   ret;
    pGpio = libsoc_gpio_request(libsoc_board_gpio_id(m_pConfig, strName.toLocal8Bit().constData()), LS_SHARED);
    if (pGpio == nullptr) {
        qDebug() << "gpio request failed";
        ret = EXIT_FAILURE;
    } else {
        if (libsoc_gpio_set_direction(pGpio, direction) == EXIT_FAILURE) {
            qDebug() << "Failed to set gpio direction";
            ret = EXIT_FAILURE;
        }
    }
    m_gpios[strName] = pGpio;
    return ret;
}

int QSoc::setLevel(QString strName, gpio_level level) {
    int ret = LEVEL_ERROR;

    if (m_gpios[strName] != NULL)
        ret = libsoc_gpio_set_level(m_gpios[strName], level);

    return ret;
}

gpio_level QSoc::level(QString strName) {
    gpio_level ret = LEVEL_ERROR;
    if (m_gpios[strName] != NULL)
        ret = libsoc_gpio_get_level(m_gpios[strName]);

    return ret;
}

int QSoc::enableInterrupt(QString strName, gpio_edge edge, int (*callback_fn)(void *), void *ptr) {
    int ret = EXIT_FAILURE;
    if (m_pGpioInterrupts[strName] == NULL) {

        m_pGpioInterrupts[strName] = libsoc_gpio_request(libsoc_board_gpio_id(m_pConfig, strName.toLocal8Bit().constData()), LS_SHARED);
        if (m_pGpioInterrupts[strName] == NULL) {
            qDebug() << "gpio request failed for interrupt";
        } else {
            int fret = libsoc_gpio_set_direction(m_pGpioInterrupts[strName], INPUT);
            if (fret == EXIT_FAILURE) {
                qDebug() << "Failed to set interrupt direction";
            } else {
                int fret = libsoc_gpio_set_edge(m_pGpioInterrupts[strName], edge);
                if (fret == EXIT_FAILURE) {
                    qDebug() << "Failed to set interrupt edge";
                } else {
                    int fret = libsoc_gpio_callback_interrupt(m_pGpioInterrupts[strName], callback_fn, ptr);
                    if (fret == EXIT_FAILURE) {
                        qDebug() << "Failed to set interrupt callback";
                    }
                }
            }
            ret = EXIT_SUCCESS;
        }
    }
    return ret;
}

int QSoc::setDirection(QString strName, gpio_direction dir) {
    int ret = EXIT_FAILURE;
    if (m_gpios[strName] != NULL) {
        ret = libsoc_gpio_set_direction(m_gpios[strName], dir);
    }
    return ret;
}

void QSoc::disableInterrupt(QString strName) {
    if (m_pGpioInterrupts[strName] != NULL) {
        libsoc_gpio_callback_interrupt_cancel(m_pGpioInterrupts[strName]);
        m_pGpioInterrupts.remove(strName);
    }
}

#include "imx6io.h"
#include <qthread.h>
#include <QTimer>


imx6io::imx6io(QObject *parent):
    QObject (parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    m_direction = DIRECTION_ERROR;
    m_value     = LEVEL_ERROR;
}
imx6io::~imx6io()
{
}
QString imx6io::getName()
{
    return m_strName;
}
void imx6io::setName(QString strName)
{
    if (m_strName.isEmpty()) {
        m_strName = strName;
        m_soc.addNewGPIO (strName, gpio_direction::INPUT);
        m_soc.disableInterrupt (m_strName);
        UpdateIO();
    }
}
void imx6io::setDirection(imx6io::IODirection dir)
{
    gpio_direction gpdir;

    if (dir == IODirection::Input) gpdir  = gpio_direction::INPUT;
    if (dir == IODirection::Output) gpdir = gpio_direction::OUTPUT;
    m_direction = gpdir;
    UpdateIO();
}
void imx6io::setValue(imx6io::IOValue val)
{
    gpio_level gpValue;

    if (val == IOValue::High) gpValue  = gpio_level::HIGH;
    if (val == IOValue::Low) gpValue = gpio_level::LOW;
    m_value = gpValue;
    UpdateIO();
}
imx6io::IOValue imx6io::getValue()
{
    IOValue val = VALUE_ERROR;
    gpio_level gplevel;

    if (!m_strName.isNull()) {
        gplevel = m_soc.level (m_strName);
        if (gplevel == gpio_level::HIGH) val = IOValue::High;
        if (gplevel == gpio_level::LOW)  val = IOValue::Low;
    }
    return val;
}
void imx6io::UpdateIO()
{
    if (!m_strName.isEmpty()) {
        if (m_direction != DIRECTION_ERROR) {
            m_soc.setDirection (m_strName,m_direction);
            if (m_direction == INPUT) {
                m_soc.enableInterrupt(m_strName, BOTH, callbackButton, this);
            }
        }
        if (m_value != LEVEL_ERROR) {
            m_soc.setLevel (m_strName, m_value);
        }
    }
}
int imx6io::callbackButton(void *ptr)
{
    imx6io *myPtr = (imx6io *)ptr;
    IOValue actLevel = myPtr->getValue();
    for (int n=0;n<30;n++) {
        if (myPtr->getValue() != actLevel) {
            actLevel = myPtr->getValue();
            n=0;
        }
        QThread::msleep(1);
    }
    actLevel = myPtr->getValue();
    if (actLevel == IOValue::Low)
        emit myPtr->pressed();
    else
        emit myPtr->released();

    emit myPtr->valueChanged(actLevel);
    return EXIT_SUCCESS;
}

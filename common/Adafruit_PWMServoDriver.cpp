
/***************************************************
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_PWMServoDriver.h>
#include <QDebug>
#include <QThread>
#include <QtGlobal>
#include <math.h>
#include <string.h>

Adafruit_PWMServoDriver::Adafruit_PWMServoDriver() {
    m_i2c.setAddress(0x40);
}
Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(quint8 addr) {
    m_i2c.setAddress(addr);
}

void Adafruit_PWMServoDriver::begin(void) {
    reset();
    setPWMFreq(50);
}

void Adafruit_PWMServoDriver::reset(void) {
    int errnr;
    errnr = m_i2c.WriteReg8(PCA9685_MODE1, 0x0);
    //    errnr = wiringPiI2CWriteReg8 (m_iDevice, PCA9685_MODE1, 0);
    if (errnr < 0) {
        m_i2c.close();
        qDebug() << strerror(errnr);
    }
    QThread::msleep(10);
}

void Adafruit_PWMServoDriver::setPWMFreq(float freq) {
    freq *= 0.9; // Correct for overshoot in the frequency setting (see issue #11).
    float prescaleval = 25000000.0;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1.0;
    quint8 prescale = floor(prescaleval + 0.5);

    quint8 oldmode = m_i2c.ReadReg8(PCA9685_MODE1);

    quint8 newmode = (oldmode & 0x7F) | 0x10; // sleep
    m_i2c.WriteReg8(PCA9685_MODE1, newmode);
    m_i2c.WriteReg8(PCA9685_PRESCALE, (int)floor(prescale)); // set the prescaler
    m_i2c.WriteReg8(PCA9685_MODE1, oldmode);
    QThread::msleep(5);
    //    m_i2c.WriteReg8 (PCA9685_MODE1, oldmode | 0xa0);  //  This sets the MODE1 register to turn on auto increment.
}

void Adafruit_PWMServoDriver::setPWM(quint8 num, quint16 on, quint16 off) {
    //    unsigned char buffer[4];
    //    buffer[0]=on&0xff;
    //    buffer[1]=on>>8;
    //    buffer[2]=off&0xff;
    //    buffer[3]=off>>8;
    //    m_i2c.send (LED0_ON_L+4*num, buffer, 4);

    m_i2c.WriteReg8(LED0_ON_L + (4 * num), on & 0xff);
    m_i2c.WriteReg8(LED0_ON_H + (4 * num), on >> 8);
    m_i2c.WriteReg8(LED0_OFF_L + (4 * num), off & 0xff);
    m_i2c.WriteReg8(LED0_OFF_H + (4 * num), off >> 8);
}
/*
void Adafruit_PWMServoDriver::setPulse(quint8 n, double pulse)
{
    double pulselength;

    pulselength = 1000000;
    pulselength /= 60;
    pulselength /= 4096;
    pulse *= 1000;
    pulse /= pulselength;
    pwm.setPWM(n, 0, pulse);
    degrees = map(pulselength, SERVOMIN, SERVOMAX, 0, 180);
}

void setServoPulse(quint8 n, double pulse)
{
  double pulselength;

  pulselength = 1000000;
  pulselength /= 60;
  pulselength /= 4096;
  pulse *= 1000;
  pulse /= pulselength;
  pwm.setPWM(n, 0, pulse);
  degrees = map(pulselength, SERVOMIN, SERVOMAX, 0, 180);
}
*/


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

#include <QDebug>
#include <Adafruit_PWMServoDriver.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <QThread>
#include <QtGlobal>

Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(quint8 addr)
{
  m_i2caddr = addr;
}

void Adafruit_PWMServoDriver::begin(void)
{
    wiringPiSetupGpio();
    m_iDevice = wiringPiI2CSetup(0x40);
    reset();
}

void Adafruit_PWMServoDriver::reset(void)
{
    int errnr;
    errnr = wiringPiI2CWriteReg8 (m_iDevice, PCA9685_MODE1, 0);
    qDebug() << strerror(errnr);

}

void Adafruit_PWMServoDriver::setPWMFreq(float freq)
{
    //Serial.print("Attempting to set freq ");
    //Serial.println(freq);
    freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
    float prescaleval = 25000000.0;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1.0;
    uint8_t prescale = floor(prescaleval + 0.5);

    uint8_t oldmode = wiringPiI2CReadReg8(m_iDevice, PCA9685_MODE1);
    uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
    wiringPiI2CWriteReg8 (m_iDevice, PCA9685_MODE1, newmode); // go to sleep
    wiringPiI2CWriteReg8 (m_iDevice, PCA9685_PRESCALE, (int) floor(prescale)); // set the prescaler
    wiringPiI2CWriteReg8 (m_iDevice, PCA9685_MODE1, oldmode);
    QThread::msleep(5);
    wiringPiI2CWriteReg8 (m_iDevice, PCA9685_MODE1, oldmode | 0x80);  //  This sets the MODE1 register to turn on auto increment.
                                                                       // This is why the beginTransmission below was not working.
}

void Adafruit_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off)
{
    int errnr;
    errnr = wiringPiI2CWriteReg8 (m_iDevice, LED0_ON_L+4*num, on & 0xff);
//    qDebug() << "write 0x" << hex << (on & 0xFF) << " to register 0x" << hex << (LED0_ON_H + 4 * num) << strerror(errnr);


    errnr = wiringPiI2CWriteReg8 (m_iDevice, LED0_ON_H+4*num, on>>8);
//    qDebug() << "write 0x" << hex << (on>>8) << " to register 0x" << hex << (LED0_ON_L + 4 * num) << strerror(errnr);

    errnr = wiringPiI2CWriteReg8 (m_iDevice, LED0_OFF_L+4*num, off & 0xff);
//    qDebug() << "write 0x" << hex << (off & 0xFF) << " to register 0x" << hex << (LED0_OFF_H + 4 * num) << strerror(errnr);

    errnr = wiringPiI2CWriteReg8 (m_iDevice, LED0_OFF_H+4*num, off>>8);
//    qDebug() << "write 0x" << hex << (off>>8) << " to register 0x" << hex << (LED0_OFF_L + 4 * num) << strerror(errnr);

}
/*
void Adafruit_PWMServoDriver::setPulse(uint8_t n, double pulse)
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

void setServoPulse(uint8_t n, double pulse)
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

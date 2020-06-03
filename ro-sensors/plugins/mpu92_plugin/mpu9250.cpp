#include <QDebug>
#include <QThread>
#include <math.h>
#include "mpu9250.h"

mpu9250::mpu9250(QObject *parent) : QObject(parent)
{
    m_i2c9250.setAddress (MPU9250_ADDRESS);
    m_i2cMagneto.setAddress (AK8963_ADDRESS);
    qint8 whoami = m_i2c9250.ReadReg8(WHO_AM_I_MPU9250);
    if (whoami!=0x73) {
        QString strMsg = QString ("MPU950 I am %1. I should be 0x73").arg(whoami);
        throw std::runtime_error (strMsg.toLocal8Bit().constData());
    }

    QVector3D gyroBias;
    QVector3D accelBias;
    calibrateMPU9250(&gyroBias, &accelBias);
    initMPU9250();
    quint8 d = m_i2cMagneto.ReadReg8(AK8963_WHO_AM_I);
    if (d!=0x48) {
        QString strMsg = QString ("AK8963 I am 0x%1. I should be 0x48").arg(d,0,16);
        throw std::runtime_error (strMsg.toLocal8Bit().constData());
    }
    initAK8963(m_magCalibration);

    m_pTimer = new QTimer(this);
    connect (m_pTimer,SIGNAL (timeout()), this, SLOT(onTimeout()));
    m_pTimer->start(10);

}

void mpu9250::initMPU9250()
{
    // wake up device
    m_i2c9250.WriteReg8(PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
    QThread::msleep(100); // Wait for all registers to reset

    // get stable time source
    m_i2c9250.WriteReg8(PWR_MGMT_1, 0x01);  // Auto select clock source to be PLL gyroscope reference if ready else
    QThread::msleep(200);


    // Configure Gyro and Thermometer
    // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively;
    // minimum QThread::msleep time for this setting is 5.9 ms, which means sensor fusion update rates cannot
    // be higher than 1 / 0.0059 = 170 Hz
    // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
    // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
    m_i2c9250.WriteReg8(CONFIG, 0x03);

    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    m_i2c9250.WriteReg8(SMPLRT_DIV, 0x04);  // Use a 200 Hz rate; a rate consistent with the filter update rate
    // determined inset in CONFIG above

    // Set gyroscope full scale range
    // Range selects FS_SEL and GFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
    quint8 c = m_i2c9250.ReadReg8(GYRO_CONFIG); // get current GYRO_CONFIG register value
    // c = c & ~0xE0; // Clear self-test bits [7:5]
    c = c & ~0x03; // Clear Fchoice bits [1:0]
    c = c & ~0x18; // Clear GFS bits [4:3]
    c = c | m_Gscale << 3; // Set full scale range for the gyro
    // c =| 0x00; // Set Fchoice for the gyro to 11 by writing its inverse to bits 1:0 of GYRO_CONFIG
    m_i2c9250.WriteReg8(GYRO_CONFIG, c ); // Write new GYRO_CONFIG value to register

    // Set accelerometer full-scale range configuration
    c = m_i2c9250.ReadReg8(ACCEL_CONFIG); // get current ACCEL_CONFIG register value
    // c = c & ~0xE0; // Clear self-test bits [7:5]
    c = c & ~0x18;  // Clear AFS bits [4:3]
    c = c | m_Ascale << 3; // Set full scale range for the accelerometer
    m_i2c9250.WriteReg8(ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value

    // Set accelerometer sample rate configuration
    // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
    // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
    c = m_i2c9250.ReadReg8(ACCEL_CONFIG2); // get current ACCEL_CONFIG2 register value
    c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
    c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
    m_i2c9250.WriteReg8(ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value
    // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
    // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

    // Configure Interrupts and Bypass Enable
    // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
    // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips
    // can join the I2C bus and all can be controlled by the Arduino as master
    m_i2c9250.WriteReg8(INT_PIN_CFG, 0x22);
    m_i2c9250.WriteReg8(INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
    QThread::msleep(100);
}

void mpu9250::initAK8963(float * destination)
{
    // First extract the factory calibration for each magnetometer axis
    qint8 rawData[3];  // x/y/z gyro calibration data stored here
    m_i2cMagneto.WriteReg8(AK8963_CNTL, 0x00); // Power down magnetometer
    QThread::msleep(10);
    m_i2cMagneto.WriteReg8(AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
    QThread::msleep(10);
    m_i2cMagneto.ReadBytes(AK8963_ASAX, rawData, 3);  // Read the x-, y-, and z-axis calibration values
    destination[0] =  (float)(rawData[0] - 128)/256. + 1.;   // Return x-axis sensitivity adjustment values, etc.
    destination[1] =  (float)(rawData[1] - 128)/256. + 1.;
    destination[2] =  (float)(rawData[2] - 128)/256. + 1.;
    m_i2cMagneto.WriteReg8 (AK8963_CNTL, 0x00); // Power down magnetometer
    QThread::msleep(10);
    // Configure the magnetometer for continuous read and highest resolution
    // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
    // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
    m_i2cMagneto.WriteReg8(AK8963_CNTL, m_Mscale << 4 | m_Mmode); // Set magnetometer data resolution and sample ODR
    QThread::msleep(10);
}

void mpu9250::readAccelData()
{
    QVector3D vector;
    qint16 accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
    qint8 rawData[6];  // x/y/z accel register data stored here

    m_i2c9250.ReadBytes(ACCEL_XOUT_H, rawData,6);  // Read the six raw data registers into data array
    accelCount[0] = ((qint16)rawData[0] << 8) | rawData[1];  // Turn the MSB and LSB into a signed 16-bit value
    accelCount[1] = ((qint16)rawData[2] << 8) | rawData[3];
    accelCount[2] = ((qint16)rawData[4] << 8) | rawData[5];

    float aRes = getAres();
    // Now we'll calculate the accleration value into actual g's
    vector.setX((float)accelCount[0]*aRes); // - accelBias[0];  // get actual g value, this depends on scale being set
    vector.setY((float)accelCount[1]*aRes); // - accelBias[1];
    vector.setZ((float)accelCount[2]*aRes); // - accelBias[2];
    m_accelPos = vector;
}

void mpu9250::readGyroData()
{
    QVector3D vector;
    qint16 destination[3];  // Stores the 16-bit signed accelerometer sensor output
    qint8 rawData[6];  // x/y/z accel register data stored here
    m_i2c9250.ReadBytes(GYRO_XOUT_H, rawData, 6);  // Read the six raw data registers sequentially into data array
//    qDebug() << rawData[0] << rawData[1] << ":" << rawData[2] << rawData[3] << ":" << rawData[4] << ":" << rawData[5];
    destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
    destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;
    destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ;

    float gRes = getGres();
    // Calculate the gyro value into actual degrees per second
    vector.setX((float)destination[0]*gRes);  // get actual gyro value, this depends on scale being set
    vector.setY((float)destination[1]*gRes);
    vector.setZ((float)destination[2]*gRes);
    m_gyroPos = vector;
}

void mpu9250::readMagData()
{
    QVector3D vector;
    qint16 destination[3];  // Stores the 16-bit signed accelerometer sensor output
    qint8 rawData[7];      // x/y/z accel register data stored here
    float magbias[3]={0,0,0};

    if(m_i2cMagneto.ReadReg8(AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
        m_i2cMagneto.ReadBytes(AK8963_XOUT_L, rawData, 7);  // Read the six raw data and ST2 registers sequentially into data array
        qint8 c = rawData[6]; // End data read by reading ST2 register
        if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
            destination[0] = ((qint16)rawData[1] << 8) | rawData[0] ;  // Turn the MSB and LSB into a signed 16-bit value
            destination[1] = ((qint16)rawData[3] << 8) | rawData[2] ;  // Data stored as little Endian
            destination[2] = ((qint16)rawData[5] << 8) | rawData[4] ;

            float mRes = getMres();
            magbias[0] = +470.;  // User environmental x-axis correction in milliGauss, should be automatically calculated
            magbias[1] = +120.;  // User environmental x-axis correction in milliGauss
            magbias[2] = +125.;  // User environmental x-axis correction in milliGauss

            // Calculate the magnetometer values in milliGauss
            // Include factory calibration per data sheet and user environmental corrections
            vector.setX((float)destination[0]*mRes*m_magCalibration[0] - magbias[0]);  // get actual magnetometer value, this depends on scale being set
            vector.setY((float)destination[1]*mRes*m_magCalibration[1] - magbias[1]);
            vector.setZ((float)destination[2]*mRes*m_magCalibration[2] - magbias[2]);
        }
        m_magPos=vector;
    }
}

float mpu9250::getTemperature()
{
    float temperature;
    qint8 rawData[2];
    m_i2c9250.ReadBytes(TEMP_OUT_H, rawData, 2);  // Read the two raw data registers sequentially into data array
    qint16 tempCount = ((qint16)rawData[0] << 8) | rawData[1];
    temperature = ((float) tempCount) / 333.87 + 21.0; // Temperature in degrees Centigrade
    return temperature;  // Turn the MSB and LSB into a 16-bit value
}

float mpu9250::getAres()
{
    float aRes=0;
    switch (m_Ascale) {
    // Possible accelerometer scales (and their register bit settings) are:
    // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
    // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
        case AFS_2G:
            aRes = 2.0/32768.0;
        break;

        case AFS_4G:
            aRes = 4.0/32768.0;
        break;

        case AFS_8G:
            aRes = 8.0/32768.0;
        break;

        case AFS_16G:
            aRes = 16.0/32768.0;
        break;
    }

    return aRes;
}

float mpu9250::getGres()
{
    float gRes=0;
    switch (m_Gscale) {
        // Possible gyro scales (and their register bit settings) are:
        // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
        case GFS_250DPS:
            gRes = 250.0/32768.0;
        break;

        case GFS_500DPS:
            gRes = 500.0/32768.0;
        break;

        case GFS_1000DPS:
            gRes = 1000.0/32768.0;
        break;

        case GFS_2000DPS:
            gRes = 2000.0/32768.0;
        break;
    }
    return gRes;
}

float mpu9250::getMres()
{
    float mRes=0;
    switch (m_Mscale) {
        // Possible magnetometer scales (and their register bit settings) are:
        // 14 bit resolution (0) and 16 bit resolution (1)
        case MFS_14BITS:
            mRes = 10.*4912./8190.; // Proper scale to return milliGauss
        break;
        case MFS_16BITS:
            mRes = 10.*4912./32760.0; // Proper scale to return milliGauss
        break;
    }
    return mRes;
}

quint8 mpu9250::interruptStatus()
{
    quint8 status;
    status = m_i2c9250.ReadReg8(INT_STATUS);
    return status;
}

QVector3D mpu9250::getGyroPosition()
{
    return m_gyroPos;
}

QVector3D mpu9250::getAccelPosition()
{
    return m_accelPos;
}

QVector3D mpu9250::getMagPosition()
{
    return m_magPos;
}

// Function which accumulates gyro and accelerometer data after device initialization. It calculates the average
// of the at-rest readings and then loads the resulting offsets into accelerometer and gyro bias registers.
void mpu9250::calibrateMPU9250(QVector3D *dest1, QVector3D *dest2)
{
    qint8 data[12]; // data array to hold accelerometer and gyro x, y, z, data
    quint16 ii, packet_count, fifo_count;
    quint32 gyro_bias[3]  = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

    // reset device
    m_i2c9250.WriteReg8(PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
    QThread::msleep(100);

    // get stable time source; Auto select clock source to be PLL gyroscope reference if ready
    // else use the internal oscillator, bits 2:0 = 001
    m_i2c9250.WriteReg8(PWR_MGMT_1, 0x01);
    m_i2c9250.WriteReg8(PWR_MGMT_2, 0x00);
    QThread::msleep(200);

    // Configure device for bias calculation
    m_i2c9250.WriteReg8(INT_ENABLE, 0x00);   // Disable all interrupts
    m_i2c9250.WriteReg8(FIFO_EN, 0x00);      // Disable FIFO
    m_i2c9250.WriteReg8(PWR_MGMT_1, 0x00);   // Turn on internal clock source
    m_i2c9250.WriteReg8(I2C_MST_CTRL, 0x00); // Disable I2C master
    m_i2c9250.WriteReg8(USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
    m_i2c9250.WriteReg8(USER_CTRL, 0x0C);    // Reset FIFO and DMP
    QThread::msleep(15);

    // Configure MPU6050 gyro and accelerometer for bias calculation
    m_i2c9250.WriteReg8(CONFIG, 0x01);      // Set low-pass filter to 188 Hz
    m_i2c9250.WriteReg8(SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
    m_i2c9250.WriteReg8(GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
    m_i2c9250.WriteReg8(ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

    quint16  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
    quint16  accelsensitivity = 16384;  // = 16384 LSB/g

    // Configure FIFO to capture accelerometer and gyro data for bias calculation
    m_i2c9250.WriteReg8(USER_CTRL, 0x40);   // Enable FIFO
    m_i2c9250.WriteReg8(FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO  (max size 512 bytes in MPU-9150)
    QThread::msleep(40); // accumulate 40 samples in 40 milliseconds = 480 bytes

    // At end of sample accumulation, turn off FIFO sensor read
    m_i2c9250.WriteReg8(FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
    m_i2c9250.ReadBytes(FIFO_COUNTH, data, 2); // read FIFO sample count
    fifo_count = ((quint16)data[0] << 8) | data[1];
    packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

    for (ii = 0; ii < packet_count; ii++) {
        quint16 accel_temp[3] = {0, 0, 0};
        quint16 gyro_temp[3] = {0, 0, 0};

        m_i2c9250.ReadBytes(FIFO_R_W, data, 12); // read data for averaging
        accel_temp[0] = (qint16) (((qint16)data[0] << 8) | data[1] );  // Form signed 16-bit integer for each sample in FIFO
        accel_temp[1] = (qint16) (((qint16)data[2] << 8) | data[3] );
        accel_temp[2] = (qint16) (((qint16)data[4] << 8) | data[5] );
        gyro_temp[0]  = (qint16) (((qint16)data[6] << 8) | data[7] );
        gyro_temp[1]  = (qint16) (((qint16)data[8] << 8) | data[9] );
        gyro_temp[2]  = (qint16) (((qint16)data[10]<< 8) | data[11]);

        accel_bias[0] += (qint32) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
        accel_bias[1] += (qint32) accel_temp[1];
        accel_bias[2] += (qint32) accel_temp[2];
        gyro_bias[0]  += (qint32) gyro_temp[0];
        gyro_bias[1]  += (qint32) gyro_temp[1];
        gyro_bias[2]  += (qint32) gyro_temp[2];
    }

    accel_bias[0] /= (qint32) packet_count; // Normalize sums to get average count biases
    accel_bias[1] /= (qint32) packet_count;
    accel_bias[2] /= (qint32) packet_count;
    gyro_bias[0]  /= (qint32) packet_count;
    gyro_bias[1]  /= (qint32) packet_count;
    gyro_bias[2]  /= (qint32) packet_count;

    if(accel_bias[2] > 0L)
        accel_bias[2] -= (qint32) accelsensitivity;  // Remove gravity from the z-axis accelerometer bias calculation
    else
        accel_bias[2] += (qint32) accelsensitivity;

    // Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
    data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
    data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
    data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
    data[3] = (-gyro_bias[1]/4)       & 0xFF;
    data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
    data[5] = (-gyro_bias[2]/4)       & 0xFF;

    // Push gyro biases to hardware registers
    m_i2c9250.WriteReg8(XG_OFFSET_H, data[0]);
    m_i2c9250.WriteReg8(XG_OFFSET_L, data[1]);
    m_i2c9250.WriteReg8(YG_OFFSET_H, data[2]);
    m_i2c9250.WriteReg8(YG_OFFSET_L, data[3]);
    m_i2c9250.WriteReg8(ZG_OFFSET_H, data[4]);
    m_i2c9250.WriteReg8(ZG_OFFSET_L, data[5]);

    // Output scaled gyro biases for display in the main program
    dest1->setX((float) gyro_bias[0]/(float) gyrosensitivity);
    dest1->setY((float) gyro_bias[1]/(float) gyrosensitivity);
    dest1->setZ((float) gyro_bias[2]/(float) gyrosensitivity);

    // Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
    // factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
    // non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
    // compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
    // the accelerometer biases calculated above must be divided by 8.

    qint32 accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
    m_i2c9250.ReadBytes(XA_OFFSET_H, data, 2); // Read factory accelerometer trim values
    accel_bias_reg[0] = (qint32) (((qint16)data[0] << 8) | data[1]);
    m_i2c9250.ReadBytes(YA_OFFSET_H, data, 2);
    accel_bias_reg[1] = (qint32) (((qint16)data[0] << 8) | data[1]);
    m_i2c9250.ReadBytes(ZA_OFFSET_H, data, 2);
    accel_bias_reg[2] = (qint32) (((qint16)data[0] << 8) | data[1]);

    quint32 mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
    quint8 mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis

    for(ii = 0; ii < 3; ii++) {
        if((accel_bias_reg[ii] & mask)) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
    }

    // Construct total accelerometer bias, including calculated average accelerometer bias from above
    accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
    accel_bias_reg[1] -= (accel_bias[1]/8);
    accel_bias_reg[2] -= (accel_bias[2]/8);

    data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
    data[1] = (accel_bias_reg[0])      & 0xFF;
    data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
    data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
    data[3] = (accel_bias_reg[1])      & 0xFF;
    data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
    data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
    data[5] = (accel_bias_reg[2])      & 0xFF;
    data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

    // Apparently this is not working for the acceleration biases in the MPU-9250
    // Are we handling the temperature correction bit properly?
    // Push accelerometer biases to hardware registers
//    m_i2c9250.WriteReg8(XA_OFFSET_H, data[0]);
//    m_i2c9250.WriteReg8(XA_OFFSET_L, data[1]);
//    m_i2c9250.WriteReg8(YA_OFFSET_H, data[2]);
//    m_i2c9250.WriteReg8(YA_OFFSET_L, data[3]);
//    m_i2c9250.WriteReg8(ZA_OFFSET_H, data[4]);
//    m_i2c9250.WriteReg8(ZA_OFFSET_L, data[5]);

    // Output scaled accelerometer biases for display in the main program
    dest2->setX((float)accel_bias[0]/(float)accelsensitivity);
    dest2->setY((float)accel_bias[1]/(float)accelsensitivity);
    dest2->setZ((float)accel_bias[2]/(float)accelsensitivity);
}

void mpu9250::enableInterrupt(QString strGPIOName, int (*callback)(void *), void *ptr)
{
    m_soc.addNewGPIO(strGPIOName,gpio_direction::INPUT);
    m_soc.enableInterrupt(strGPIOName, RISING, callback, ptr);
}

void mpu9250::selfTest(float *destination)
{
    qint8 rawData[6]= {0,0,0,0,0,0};
    quint8 selfTest[6];
    qint32 gAvg[3]={0,0,0}, aAvg[3]={0,0,0}, aSTAvg[3]={0,0,0}, gSTAvg[3]={0,0,0};
    float factoryTrim[6];
    quint8 FS=0;
    int total;

    qDebug() << gAvg[0];
    qDebug() << gAvg[1];
    qDebug() << gAvg[2];

    m_i2c9250.WriteReg8(SMPLRT_DIV, 0x00);    // Set gyro sample rate to 1 kHz
    m_i2c9250.WriteReg8(CONFIG, 0x02);        // Set gyro sample rate to 1 kHz and DLPF to 92 Hz
    m_i2c9250.WriteReg8(GYRO_CONFIG, FS<<3);  // Set full scale range for the gyro to 250 dps
    m_i2c9250.WriteReg8(ACCEL_CONFIG2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
    m_i2c9250.WriteReg8(ACCEL_CONFIG, FS<<3); // Set full scale range for the accelerometer to 2 g

    for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
        total=m_i2c9250.ReadBytes(ACCEL_XOUT_H, rawData, 6);        // Read the six raw data registers into data array
        if (total<6) {
            qDebug() << "Error reading ACCEL_XOUT_H 1";
            return;
        }
        aAvg[0] += (qint16)(((qint16)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
        aAvg[1] += (qint16)(((qint16)rawData[2] << 8) | rawData[3]) ;
        aAvg[2] += (qint16)(((qint16)rawData[4] << 8) | rawData[5]) ;

        total=m_i2c9250.ReadBytes(GYRO_XOUT_H, rawData, 6);       // Read the six raw data registers sequentially into data array
        if (total<6) {
            qDebug() << "Error reading GYRO_XOUT_H 1";
            return;
        }
        gAvg[0] += (qint16)(((qint16)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
        gAvg[1] += (qint16)(((qint16)rawData[2] << 8) | rawData[3]) ;
        gAvg[2] += (qint16)(((qint16)rawData[4] << 8) | rawData[5]) ;
    }

    for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
        aAvg[ii] /= 200;
        gAvg[ii] /= 200;
    }

    // Configure the accelerometer for self-test
    m_i2c9250.WriteReg8(ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
    m_i2c9250.WriteReg8(GYRO_CONFIG,  0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
    QThread::msleep(25);  // Delay a while to let the device stabilize

    for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
        total=m_i2c9250.ReadBytes (ACCEL_XOUT_H, rawData, 6);  // Read the six raw data registers into data array
        if (total<6) {
            qDebug() << "Error reading ACCEL_XOUT_H 2";
            return;
        }
        aSTAvg[0] += (qint16)(((qint16)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
        aSTAvg[1] += (qint16)(((qint16)rawData[2] << 8) | rawData[3]) ;
        aSTAvg[2] += (qint16)(((qint16)rawData[4] << 8) | rawData[5]) ;

        total=m_i2c9250.ReadBytes(GYRO_XOUT_H, rawData, 6);  // Read the six raw data registers sequentially into data array
        if (total<6) {
            qDebug() << "Error reading GYRO_XOUT_H 2";
            return;
        }
        gSTAvg[0] += (qint16)(((qint16)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
        gSTAvg[1] += (qint16)(((qint16)rawData[2] << 8) | rawData[3]) ;
        gSTAvg[2] += (qint16)(((qint16)rawData[4] << 8) | rawData[5]) ;
    }

    for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average self-test readings
        aSTAvg[ii] /= 200;
        gSTAvg[ii] /= 200;
    }

//   Configure the gyro and accelerometer for normal operation
     m_i2c9250.WriteReg8(ACCEL_CONFIG, 0x00);
     m_i2c9250.WriteReg8(GYRO_CONFIG,  0x00);
     QThread::msleep(25);  // Delay a while to let the device stabilize

     // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
     selfTest[0] = m_i2c9250.ReadReg8(SELF_TEST_X_ACCEL); // X-axis accel self-test results
     selfTest[1] = m_i2c9250.ReadReg8(SELF_TEST_Y_ACCEL); // Y-axis accel self-test results
     selfTest[2] = m_i2c9250.ReadReg8(SELF_TEST_Z_ACCEL); // Z-axis accel self-test results
     selfTest[3] = m_i2c9250.ReadReg8(SELF_TEST_X_GYRO);  // X-axis gyro self-test results
     selfTest[4] = m_i2c9250.ReadReg8(SELF_TEST_Y_GYRO);  // Y-axis gyro self-test results
     selfTest[5] = m_i2c9250.ReadReg8(SELF_TEST_Z_GYRO);  // Z-axis gyro self-test results

    // Retrieve factory self-test value from self-test code reads
     factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); // FT[Xa] factory trim calculation
     factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); // FT[Ya] factory trim calculation
     factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); // FT[Za] factory trim calculation
     factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); // FT[Xg] factory trim calculation
     factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) )); // FT[Yg] factory trim calculation
     factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); // FT[Zg] factory trim calculation

//   Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
//   To get percent, must multiply by 100
     for (int i = 0; i < 3; i++) {
       destination[i]   = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i] - 100.;   // Report percent differences
       destination[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3] - 100.; // Report percent differences
     }
}

void mpu9250::onTimeout()
{
    QVector3D vector;
    quint8 status = interruptStatus();
    if (status&01) {
        readAccelData();
        readGyroData();
        readMagData();
    }

//    // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of the magnetometer;
//    // the magnetometer z-axis (+ down) is opposite to z-axis (+ up) of accelerometer and gyro!
//    // We have to make some allowance for this orientationmismatch in feeding the output to the quaternion filter.
//    // For the MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward along the x-axis just like
//    // in the LSM9DS0 sensor. This rotation can be modified to allow any convenient orientation convention.
//    // This is ok by aircraft orientation standards!
//    // Pass gyro rate as rad/s
//    //  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
//    MahonyQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f, my, mx, mz);


}

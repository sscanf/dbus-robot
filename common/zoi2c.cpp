#include <QDebug>
#include <zoi2c.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

//*******************************************************************
// Class for accessing GNUBLIN i2c Bus
//*******************************************************************
#define DEFAULTDEVICE "/dev/i2c-4"

zoi2c::zoi2c(QObject *parent)
    : QObject(parent) {
    init(DEFAULTDEVICE, -1);
}

zoi2c::zoi2c(int Address, QObject *parent)
    : QObject(parent) {
    init(DEFAULTDEVICE, Address);
}

zoi2c::zoi2c(QString Devicefile, int Address, QObject *parent)
    : QObject(parent) {
    init(Devicefile, Address);
}

zoi2c::~zoi2c() {
    close_fd();
}

void zoi2c::init(QString Devicefile, int Address) {
    devicefile    = Devicefile;
    slave_address = Address;
    error_flag    = false;
    fd            = 0;
}

int zoi2c::errorMsg(QString message) {
    ErrorMessage = message;
    error_flag   = true;
    close_fd();
    return -1;
}

void zoi2c::close_fd() {
    if (fd) {
        ::close(fd);
        fd = 0;
    }
}

int zoi2c::open_fd() {
    error_flag = false;

    if (fd) {
        close_fd();
        fd = 0;
    }

    if (slave_address == -1)
        return errorMsg("ERROR slave address is not set\n");

    if ((fd = open(devicefile.toLocal8Bit().constData(), O_RDWR)) < 0)
        return errorMsg("ERROR opening: " + devicefile + "\n");

    if (ioctl(fd, I2C_SLAVE, slave_address) < 0)
        return errorMsg("ERROR address: " + QString("%1").arg(slave_address) + "\n");

    return 0;
}

bool zoi2c::fail() {
    return error_flag;
}

int zoi2c::setAddress(int Address) {
    slave_address = Address;
    return open_fd();
}

int zoi2c::getAddress() {
    return slave_address;
}

const char *zoi2c::getErrorMessage() {
    return ErrorMessage.toLocal8Bit().constData();
}

int zoi2c::setDevicefile(QString filename) {
    devicefile = filename;
    return open_fd();
}

int zoi2c::receive(unsigned char *RxBuf, int length) {

    if (RxBuf == nullptr)
        return errorMsg("Receive method received a null TxBuf pointer.\n");
    if (length < 1)
        return errorMsg("Receive method received an invalid buffer length.\n");

    if (!fd)
        if (open_fd() == -1)
            return -1;

    error_flag = false;

    int ret = read(fd, RxBuf, static_cast<int>(length));
    if (ret != length)
        return errorMsg(QString("i2c read error! Address: %1 dev file: %3\n").arg(slave_address).arg(devicefile));
    return ret;
}

int zoi2c::receive(unsigned char RegisterAddress, qint8 *RxBuf, int length) {
    if (RxBuf == nullptr)
        return errorMsg("Receive method received a null TxBuf pointer.\n");
    if (length < 1)
        return errorMsg("Receive method received an invalid buffer length.\n");

    if (!fd)
        if (open_fd() == -1)
            return -1;

    error_flag = false;

    if (write(fd, &RegisterAddress, 1) != 1)
        return errorMsg("i2c write error!\n");

    if (read(fd, RxBuf, static_cast<int>(length) != length))
        return errorMsg(QString("i2c read error! Address: %1 dev file: %3\n").arg(slave_address).arg(devicefile));

    return 1;
}

int zoi2c::ReadBytes(unsigned char RegisterAddress, qint8 *RxBuf, int length) {
    int n;
    for (n = 0; n < length; n++) {
        RxBuf[n] = ReadReg8(RegisterAddress + n);
        if (RxBuf[n] == -1)
            break;
    }
    return n;
}

qint8 zoi2c::ReadReg8(unsigned char RegisterAddress) {
    union i2c_smbus_data data;

    if (i2c_smbus_access(I2C_SMBUS_READ, RegisterAddress, I2C_SMBUS_BYTE_DATA, &data))
        return -1;
    else
        return data.byte & 0xFF;
}

quint32 zoi2c::i2c_smbus_access(char read_write, quint8 command, int size, union i2c_smbus_data *data) {
    struct i2c_smbus_ioctl_data args;
    args.read_write = read_write;
    args.command    = command;
    args.size       = size;
    args.data       = data;
    return ioctl(fd, I2C_SMBUS, &args);
}

int zoi2c::WriteReg8(quint8 RegisterAddress, int value) {
    union i2c_smbus_data data;
    data.byte = value;
    return i2c_smbus_access(I2C_SMBUS_WRITE, RegisterAddress, I2C_SMBUS_BYTE_DATA, &data);
}

int zoi2c::send(unsigned char registerAddress, unsigned char *buffer, int length) {

    union i2c_smbus_data data;
    int                  i;

    if (length > I2C_SMBUS_BLOCK_MAX) {
        length = I2C_SMBUS_BLOCK_MAX;
    }

    for (i = 1; i <= length; i++) {
        data.block[i] = buffer[i - 1];
    }

    data.block[0] = length;
    return i2c_smbus_access(I2C_SMBUS_WRITE, registerAddress, I2C_SMBUS_BLOCK_DATA, &data);
}

int zoi2c::send(const QByteArray &buffer) {
    int length = buffer.length();

    if (!fd)
        if (open_fd() == -1)
            return -1;

    error_flag = false;
    if (write(fd, buffer.constData(), static_cast<size_t>(length)) != length)
        return errorMsg("i2c write error!\n");

    return 1;
}

// int zoi2c::send(unsigned char RegisterAddress, unsigned char *TxBuf, int length)
//{
//     int i;
//     unsigned char data[length+1];
//     data[0]=RegisterAddress;

//    for ( i = 0; i < length ; i++ ) {
//        data[i+1] = TxBuf[i];
//    }

//    if (TxBuf == nullptr)
//        return errorMsg("Send method received a null TxBuf pointer.\n");
//    if (length < 1)
//        return errorMsg("Send method received an invalid buffer length.\n");

//    if (!fd)
//        if (open_fd() == -1)
//              return -1;

//    error_flag=false;

///*	if (send(RegisterAddress) == -1)
//        return -1;
//*/
//    if(write(fd, data, static_cast<int>(length+1) != length+1))
//        return errorMsg("i2c write error!\n");

//    return 1;
//}

int zoi2c::send(unsigned char value) {
    if (!fd)
        if (open_fd() == -1) {
            return -1;
        }

    error_flag = false;

    if (write(fd, &value, 1) != 1)
        return errorMsg("i2c write error!\n");

    return 1;
}

void zoi2c::close() {
    close_fd();
}

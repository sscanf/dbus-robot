#ifndef zoi2c_H
#define zoi2c_H

#include <QObject>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

class zoi2c : public QObject {
    Q_OBJECT

public:
    zoi2c(QObject *parent = nullptr);
    zoi2c(int Address, QObject *parent = nullptr);
    zoi2c(QString DeviceFile, int Address, QObject *parent = nullptr);
    ~zoi2c();

    bool        fail();
    int         setAddress(int Address);
    int         getAddress();
    const char *getErrorMessage();
    int         setDevicefile(QString filename);
    int         receive(unsigned char *RxBuf, int length);
    int         receive(unsigned char RegisterAddress, qint8 *RxBuf, int length);
    int         ReadBytes(unsigned char RegisterAddress, qint8 *RxBuf, int length);
    qint8       ReadReg8(unsigned char RegisterAddress);
    int         WriteReg8(quint8 RegisterAddress, int value);
    int         send(const QByteArray &buffer);
    int         send(unsigned char registerAddress, unsigned char *buffer, int length);
    int         send(unsigned char value);
    void        close();

private:
    int     errorMsg(QString message);
    int     open_fd();
    void    close_fd();
    void    init(QString DeviceFile, int Address);
    quint32 i2c_smbus_access(char read_write, quint8 command, int size, union i2c_smbus_data *data);

private:
    bool    error_flag;
    int     slave_address;
    QString devicefile;
    QString ErrorMessage;
    int     fd;
};
#endif

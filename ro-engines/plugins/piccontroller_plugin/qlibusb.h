#ifndef QLIBUSB_H
#define QLIBUSB_H

#include <QObject>
#include <libusb-1.0/libusb.h>


static const int CONTROL_REQUEST_TYPE_IN = LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE;
static const int CONTROL_REQUEST_TYPE_OUT = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE;

static const int INTERRUPT_IN_ENDPOINT = 0x81;
static const int INTERRUPT_OUT_ENDPOINT = 0x01;

static const int ENDPOINT_IN_IN=0x81;
static const int ENDPOINT_IN_OUT=0x01;

static const int HID_GET_REPORT=0x01;
static const int HID_SET_REPORT=0x09;
static const int HID_REPORT_TYPE_INPUT=0x01;
static const int HID_REPORT_TYPE_OUTPUT=0x02;
static const int HID_REPORT_TYPE_FEATURE=0x03;
static const int INTERFACE_NUMBER=0x00;

class QlibUsb : public QObject
{
    Q_OBJECT
public:
    explicit QlibUsb(QObject *parent = 0);
    int     open (int vendorId, int productId);
    void    usbRelease(void);
    int     get ( quint8 *buffer, int len);
    int     send(unsigned char *buff_out, int len);
    int     SendInterrupt ( quint8 *buffer, int len);
    int     GetInterrupt ( quint8 *buffer, int len);
    bool    isOpen ();

    ~QlibUsb();
private:
    struct libusb_device_handle *m_handle;

signals:
    
public slots:
    
};

#endif // QLIBUSB_H

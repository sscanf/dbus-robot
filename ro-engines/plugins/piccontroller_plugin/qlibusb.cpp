#include "qlibusb.h"
#include <QDebug>


QlibUsb::QlibUsb(QObject *parent) :
    QObject(parent)
{
    m_handle=0;
}

QlibUsb::~QlibUsb()
{
    if (m_handle)
        usbRelease();
}

bool QlibUsb::isOpen ()
{
    return (bool)m_handle;
}

int QlibUsb::open (int vendorId, int productId)
{
    int r; 								//for return values
    r = libusb_init(NULL); 				//initialize the library for the session we just declared
    if(r < 0)
    {
        qDebug() << "Init Error " << r;
        return 1;
    }
    libusb_set_debug(NULL, 3); //set verbosity level to 3, as suggested in the documentation

    m_handle = libusb_open_device_with_vid_pid(NULL, vendorId, productId); //these are vendorID and productID I found for my usb device
    if(m_handle == NULL)
    {
        //qDebug()<<"Cannot open device";
        return 1;
    }
    else
        qDebug() <<"Device Opened";

    libusb_detach_kernel_driver (m_handle, 0);

    r = libusb_claim_interface(m_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
    if(r < 0)
    {
        qDebug() << "Cannot Claim Interface";
        return 1;
    }

    return 0;
}


void QlibUsb::usbRelease(void)
{
    qDebug() << "Releasing device ... ";
    libusb_release_interface (m_handle,0);
    libusb_close (m_handle);
    m_handle=0;
    libusb_exit (NULL);
}

int QlibUsb::SendInterrupt ( quint8 *buffer, int len)
{

    int bytes_transferred;
    int result;

    result = libusb_interrupt_transfer (
                m_handle,
                INTERRUPT_OUT_ENDPOINT,
                buffer,
                len,
                &bytes_transferred,
                5000);

    if (result < 0)
    {
        qDebug() << "Interrupt out endpoint error";
        return 1;
    }

    return 0;
}

int QlibUsb::GetInterrupt ( quint8 *buffer, int len)
{
    int bytes_transferred;
    int result;

    result = libusb_interrupt_transfer(
                m_handle,
                INTERRUPT_IN_ENDPOINT,
                buffer,
                len,
                &bytes_transferred,
                5000);

    if (result <0 )
    {
        qDebug() << "Interrupt in endpoint error";
        return 1;
    }

    return 0;
}

int QlibUsb::get ( quint8 *buffer, int len)
{
    int bytes_received;

    bytes_received=libusb_control_transfer (m_handle,
                                 CONTROL_REQUEST_TYPE_IN,
                                 HID_GET_REPORT,
                                 (HID_REPORT_TYPE_INPUT<<8)|0x00,
                                 INTERFACE_NUMBER,
                                 buffer,
                                 len,
                                 5000);

    if(bytes_received<len) //we wrote the 4 bytes successfully
    {
        qDebug() << "Read Error: total bytes received = "<< bytes_received;
        return 1;
     }


    return 0;
}

int QlibUsb::send(unsigned char *buff_out, int len)
{
    int bytes_sent;

   bytes_sent = libusb_control_transfer (m_handle,
                                CONTROL_REQUEST_TYPE_OUT,
                                HID_SET_REPORT,
                                (HID_REPORT_TYPE_OUTPUT<<8)|0X00,
                                INTERFACE_NUMBER,
                                buff_out,
                                len,
                                5000);

   if(bytes_sent<len)
   {
        qDebug()<<"Write Error";
        return 1;
   }
   return 0;
}



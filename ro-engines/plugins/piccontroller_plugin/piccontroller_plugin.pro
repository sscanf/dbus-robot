QT += dbus multimedia

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

_INSTALL_ROOT=$$(INSTALL_ROOT)
isEmpty (_INSTALL_ROOT){
    message ("not defined");
    _INSTALL_ROOT=/
}

system ($$PWD/../tools/mkinterface.sh piccontroller_worker)

LIBS        += -lusb-1.0
INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(piccontroller-plugin)
DESTDIR      = plugins

dbus_proxy_files.path   = /usr/include/robot/
dbus_proxy_files.files  = $$PWD/proxy
config_files.path       = /etc/
config_files.files      = $$PWD/robot/

HEADERS = piccontroller_worker_interface.h   \
          piccontroller_factory.h            \
          piccontroller_worker.h \
    qlibusb.h

SOURCES  = piccontroller_worker_interface.cpp\
           piccontroller_worker.cpp          \
           piccontroller_factory.cpp \
    qlibusb.cpp

target.path = /usr/lib/
INSTALLS += target dbus_proxy_files

QMAKE_CLEAN += $$PWD/piccontroller_worker_interface.cpp       \
               $$PWD/piccontroller_worker_interface.h         \
               $$PWD/com.zitro.zone.piccontroller_manager.xml \
               -r $$PWD/proxy/*

QT += dbus
QT -= gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh piccontroller_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -r $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

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

HEADERS = piccontroller_worker_interface.h   \
          piccontroller_factory.h            \
          piccontroller_worker.h \
          qlibusb.h

SOURCES  = piccontroller_worker_interface.cpp\
           piccontroller_worker.cpp          \
           piccontroller_factory.cpp \
           qlibusb.cpp

target.path = /usr/lib/
INSTALLS += target

QMAKE_CLEAN += $$PWD/piccontroller_worker_interface.cpp       \
               $$PWD/piccontroller_worker_interface.h         \
               $$PWD/com.zitro.zone.piccontroller_manager.xml \
               -r $$PWD/proxy/*

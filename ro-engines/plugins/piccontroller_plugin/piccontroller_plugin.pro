QT += dbus
QT -= gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -Wno-cpp
QMAKE_CXXFLAGS += -Wno-cpp

system ($$PWD/../tools/mkinterface.sh piccontroller_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -r $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

LIBS        += -lusb-1.0
INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
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

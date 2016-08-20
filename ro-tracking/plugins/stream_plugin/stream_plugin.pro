QT += dbus

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

_INSTALL_ROOT=$$(INSTALL_ROOT)
isEmpty (_INSTALL_ROOT){
    message ("not defined");
    _INSTALL_ROOT=/
}

system ($$PWD/../tools/mkinterface.sh stream_worker)

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(stream-plugin)
DESTDIR      = plugins
LIBS        += -lvlc

dbus_proxy_files.path   = /usr/lib/zone/zoaudio
dbus_proxy_files.files  = $$PWD/proxy
config_files.path       = /etc/
config_files.files      = $$PWD/zone/

HEADERS = stream_worker_interface.h   \
          stream_factory.h            \
          stream_worker.h

SOURCES  = stream_worker_interface.cpp\
           stream_worker.cpp          \
           stream_factory.cpp

target.path = /usr/lib/
INSTALLS += target dbus_proxy_files

QMAKE_CLEAN += $$PWD/stream_worker_interface.cpp       \
               $$PWD/stream_worker_interface.h         \
               $$PWD/com.zitro.zone.stream_manager.xml \
               -r $$PWD/proxy/*

QT += dbus multimedia

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
DEFINES += PLUGINS_PATH=\\\"/usr/lib/zone/zoaudio\\\"

_INSTALL_ROOT=$$(INSTALL_ROOT)
isEmpty (_INSTALL_ROOT){
    message ("not defined");
    _INSTALL_ROOT=/
}

system ($$PWD/../tools/mkinterface.sh @@name@@_worker)

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(@@name@@-plugin)
DESTDIR      = plugins

dbus_proxy_files.path   = /usr/lib/zone/zoaudio
dbus_proxy_files.files  = $$PWD/proxy
config_files.path       = /etc/
config_files.files      = $$PWD/zone/

HEADERS = @@name@@_worker_interface.h   \
          @@name@@_factory.h            \
          @@name@@_worker.h

SOURCES  = @@name@@_worker_interface.cpp\
           @@name@@_worker.cpp          \
           @@name@@_factory.cpp

target.path = $$dbus_proxy_files.path
INSTALLS += target dbus_proxy_files

QMAKE_CLEAN += $$PWD/@@name@@_worker_interface.cpp       \
               $$PWD/@@name@@_worker_interface.h         \
               $$PWD/com.zitro.zone.@@name@@_manager.xml \
               -r $$PWD/proxy/*

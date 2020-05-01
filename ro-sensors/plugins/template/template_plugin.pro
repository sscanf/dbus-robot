QT += dbus multimedia

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
DEFINES += PLUGINS_PATH=\\\"/usr/lib\\\"

_INSTALL_ROOT=$$(INSTALL_ROOT)
isEmpty (_INSTALL_ROOT){
    message ("not defined");
    _INSTALL_ROOT=/
}

system ($$PWD/../tools/mkinterface.sh @@name@@_worker)
ystem ($$quote(cp -r $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(@@name@@-plugin)
DESTDIR      = plugins

sysroot_files.path       = $$(QT_SYSROOT)/etc/
sysroot_files.files      = $$PWD/robot/
sysroot_files.commands   = cp $$config.files.files $$config_files.path

dbus_files.path         = /etc/dbus-1/
dbus_files.files        = $$PWD/system.d

dbus_services.path      = /usr/share/dbus-1/
dbus_services.files     = $$PWD/system-services \
                          $$PWD/services

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
               $$PWD/com.robot.@@name@@_manager.xml \
               -r $$PWD/proxy/*

QT += dbus gamepad
QT -= gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh dualshock4_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(dualshock4-plugin)
DESTDIR      = plugins

HEADERS = dualshock4_worker_interface.h   \
          dualshock4_factory.h            \
          dualshock4_worker.h

SOURCES  = dualshock4_worker_interface.cpp\
           dualshock4_worker.cpp          \
           dualshock4_factory.cpp

target.path = /usr/lib
INSTALLS += target

QMAKE_CLEAN += $$PWD/dualshock4_worker_interface.cpp       \
               $$PWD/dualshock4_worker_interface.h         \
               $$PWD/com.robot.dualshock4_manager.xml \
               -r $$PWD/proxy/*

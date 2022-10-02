#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T10:41:01
#
#-------------------------------------------------

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
#QMAKE_CXXFLAGS += -std=c++0x

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -Wno-cpp
QMAKE_CXXFLAGS += -Wno-cpp

system ($$PWD/../tools/mkinterface.sh gamepad_manager)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -r $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml
QT          -= gui
INCLUDEPATH += ../common/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include
TARGET       = rogamepad
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     +=  main.cpp

config_files.path  = /etc/
config_files.files = $$PWD/robot/
dbus_files.path    = /etc/dbus-1/
dbus_files.files   = $$PWD/system.d/
dbus_services.path = /usr/share/dbus-1/
dbus_services.files= $$PWD/system-services


SOURCES += gamepad_manager.cpp \
           gamepad_manager_interface.cpp

HEADERS += gamepad_manager.h \
           gamepad_manager_interface.h	 \
           ../common/gamepad_plugin.h


target.path = /usr/bin/
INSTALLS += target 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/gamepad_manager_interface.cpp \
               $$PWD/gamepad_manager_interface.h   \
               $$PWD/com.robot.gamepad_manager.xml \
               -r $$PWD/proxy/*

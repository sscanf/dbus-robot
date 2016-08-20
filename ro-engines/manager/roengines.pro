#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T10:41:01
#
#-------------------------------------------------

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS += -std=c++0x

_INSTALL_ROOT=$$(INSTALL_ROOT)

system ($$PWD/../tools/mkinterface.sh roengines)

QT          += core dbus xml
QT          -= gui
INCLUDEPATH += $$(QT_SYSROOT)/usr/include
INCLUDEPATH += ../common/
TARGET       = roengines
CONFIG      += debug
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     +=  main.cpp                     \


dbus_proxy_files.path	= /usr/include/robot/
dbus_proxy_files.files	= $$PWD/proxy/
config_files.path	= /etc/
config_files.files	= $$PWD/robot/

dbus_files.path         = /etc/dbus-1/
dbus_files.files        = $$PWD/system.d/
 
dbus_services.path      = /usr/share/dbus-1/ 
dbus_services.files     = $$PWD/system-services \
                          $$PWD/services


SOURCES += roengines.cpp         \
           roengines_interface.cpp

HEADERS += roengines.h          \
           roengines_interface.h	 \
	   ../common/roengines_plugin.h


target.path = /usr/bin/
INSTALLS += target 
INSTALLS += dbus_proxy_files 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/roengines_interface.cpp \
               $$PWD/roengines_interface.h   \
               $$PWD/com.robot.roengines.xml \
               $$PWD/proxy/*

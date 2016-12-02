#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T10:41:01
#
#-------------------------------------------------

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS += -std=c++0x

_INSTALL_ROOT=$$(INSTALL_ROOT)

system ($$PWD/../tools/mkinterface.sh @@name@@_manager)
system ($$quote(cp -r $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml
QT          -= gui
INCLUDEPATH += $$(QT_SYSROOT)/usr/include
INCLUDEPATH += ../common/
TARGET       = @@name@@
CONFIG      += debug
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     +=  main.cpp                     \


config_files.path	= /etc/
config_files.files	= $$PWD/robot/

dbus_files.path         = /etc/dbus-1/
dbus_files.files        = $$PWD/system.d/
 
dbus_services.path      = /usr/share/dbus-1/ 
dbus_services.files     = $$PWD/system-services


SOURCES += @@name@@_manager.cpp         \
           @@name@@_manager_interface.cpp

HEADERS += @@name@@_manager.h          \
           @@name@@_manager_interface.h	 \
	   ../common/@@name@@_plugin.h


target.path = /usr/bin/
INSTALLS += target 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/@@name@@_manager_interface.cpp \
               $$PWD/@@name@@_manager_interface.h   \
               $$PWD/com.robot.@@name@@_manager.xml \
               $$PWD/proxy/*

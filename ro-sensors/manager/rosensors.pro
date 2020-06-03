#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T10:41:01
#
#-------------------------------------------------

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS += -std=c++0x

system ($$PWD/../tools/mkinterface.sh rosensors_manager)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -r $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml bluetooth
QT          -= gui
INCLUDEPATH += ../common/
TARGET       = rosensors
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app

config_files.path  = /etc/
config_files.files = $$PWD/robot/
dbus_files.path    = /etc/dbus-1/
dbus_files.files   = $$PWD/system.d/
dbus_services.path = /usr/share/dbus-1/
dbus_services.files= $$PWD/system-services

SOURCES += main.cpp rosensors_manager.cpp  \
           rosensors_manager_interface.cpp

HEADERS += rosensors_manager.h           \
           rosensors_manager_interface.h \
	   ../common/rosensors_plugin.h


target.path = /usr/bin/
INSTALLS += target 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/rosensors_manager_interface.cpp \
               $$PWD/rosensors_manager_interface.h   \
               $$PWD/com.robot.rosensors_manager.xml \
               -r $$PWD/proxy/*

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS += -std=c++0x

system ($$PWD/../tools/mkinterface.sh rocamera_manager)
system ($$quote(cp -r $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml
QT          -= gui
#INCLUDEPATH += $$[QT_SYSROOT]/usr/include
INCLUDEPATH += ../common/
TARGET       = rocamera
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app


config_files.path   = /etc/
config_files.files  = $$PWD/robot/

dbus_files.path     = /etc/dbus-1/
dbus_files.files    = $$PWD/system.d/
 
dbus_services.path  = /usr/share/dbus-1/
dbus_services.files = $$PWD/services


SOURCES += main.cpp \
           rocamera_manager.cpp         \
           rocamera_manager_interface.cpp

HEADERS += rocamera_manager.h          \
           rocamera_manager_interface.h	 \
	   ../common/rocamera_plugin.h

target.path = /usr/bin/
INSTALLS += target 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/rocamera_manager_interface.cpp \
               $$PWD/rocamera_manager_interface.h   \
               $$PWD/com.robot.rocamera_manager.xml \
               -r $$PWD/proxy/*

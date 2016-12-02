#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T10:41:01
#
#-------------------------------------------------

VERSION = \\\"'01.00.00'\\\"
DEFINES         += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS  += -std=c++0x

_INSTALL_ROOT=$$(INSTALL_ROOT)

system ($$PWD/../tools/mkinterface.sh rotracking_manager)
system ($$quote(mkdir $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml
QT          -= gui
INCLUDEPATH += $$(QT_SYSROOT)/usr/include
INCLUDEPATH += ../common/
TARGET       = rotracking
CONFIG      += debug
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     +=  main.cpp
LIBS        += -lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc  -lraspicam -lraspicam_cv #-lraspicam_cv -lmmal -lmmal_core -lmmal_vc_client -lmmal_util -lmmal_components -lraspicam

config_files.path	= /etc/
config_files.files	= $$PWD/robot/

dbus_files.path         = /etc/dbus-1/
dbus_files.files        = $$PWD/system.d
 
dbus_services.path      = /usr/share/dbus-1/
dbus_services.files     = $$PWD/system-services \
                          $$PWD/services

SOURCES += rotracking_manager.cpp         \
           rotracking_manager_interface.cpp

HEADERS += rotracking_manager.h          \
           rotracking_manager_interface.h\
           ../common/rotracking_plugin.h

target.path = /usr/bin/
INSTALLS += target 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/rotracking_manager_interface.cpp \
               $$PWD/rotracking_manager_interface.h   \
               $$PWD/com.robot.rotracking_manager.xml \
               -r $$PWD/proxy/*

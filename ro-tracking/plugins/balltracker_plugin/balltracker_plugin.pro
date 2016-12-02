QT += dbus network
QT += gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh balltracker_worker)
system ($$quote(mkdir $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(balltracker-plugin)
DESTDIR      = plugins
LIBS        += -lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc  -lraspicam -lraspicam_cv #-lraspicam_cv -lmmal -lmmal_core -lmmal_vc_client -lmmal_util -lmmal_components -lraspicam

sysroot_files.path       = $$(QT_SYSROOT)/etc/
sysroot_files.files      = $$PWD/zone/
sysroot_files.commands   = cp $$config.files.files $$config_files.path

dbus_files.path         = /etc/dbus-1/
dbus_files.files        = $$PWD/system.d

dbus_services.path      = /usr/share/dbus-1/
dbus_services.files     = $$PWD/system-services \
                          $$PWD/services


HEADERS = balltracker_worker_interface.h \
          balltracker_factory.h          \
          balltracker_worker.h

SOURCES  = balltracker_worker_interface.cpp\
           balltracker_worker.cpp          \
           balltracker_factory.cpp

target.path = /usr/lib/

INSTALLS += target dbus_files dbus_services

QMAKE_CLEAN += $$PWD/balltracker_worker_interface.cpp       \
               $$PWD/balltracker_worker_interface.h         \
               $$PWD/com.robot.balltracker_manager.xml \
               -r $$PWD/proxy/*

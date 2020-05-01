VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS += -std=c++0x

system ($$PWD/../tools/mkinterface.sh servoscontroller_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -r $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml
QT          -= gui
INCLUDEPATH += ../../common
#INCLUDEPATH += $$[QT_SYSROOT]/usr/include
INCLUDEPATH += ../../../common/
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(servoscontroller-plugin)
DESTDIR      = plugins

sysroot_files.path      = $$(QT_SYSROOT)/etc/
sysroot_files.files     = $$PWD/robot/
sysroot_files.commands  = cp $$config.files.files $$config_files.path

#dbus_files.path         = /etc/dbus-1/
#dbus_files.files        = $$PWD/system.d

#dbus_services.path      = /usr/share/dbus-1/
#dbus_services.files     = $$PWD/system-services \
#                          $$PWD/services

target.path = /usr/lib/

HEADERS = servoscontroller_worker_interface.h   \
          servoscontroller_factory.h            \
          servoscontroller_worker.h \
          Adafruit_PWMServoDriver.h \
          ../../../common/zoi2c.h

SOURCES  = servoscontroller_worker_interface.cpp\
           servoscontroller_worker.cpp          \
           servoscontroller_factory.cpp \
           Adafruit_PWMServoDriver.cpp \
           ../../../common/zoi2c.cpp

INSTALLS += target #dbus_files dbus_services

QMAKE_CLEAN += $$PWD/servoscontroller_worker_interface.cpp  \
               $$PWD/servoscontroller_worker_interface.h    \
               $$PWD/com.robot.servoscontroller_manager.xml \
               -r $$PWD/proxy/*

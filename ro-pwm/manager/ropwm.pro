VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
QMAKE_CXXFLAGS += -std=c++0x

system ($$PWD/../tools/mkinterface.sh pwm_manager)
system ($$quote(cp -r $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

QT          += core dbus xml
QT          -= gui
#INCLUDEPATH += $$[QT_SYSROOT]/usr/include
INCLUDEPATH += ../common/
INCLUDEPATH += ../../common/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
TARGET       = ropwm
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include


config_files.path   = /etc/
config_files.files  = $$PWD/robot/

dbus_files.path     = /etc/dbus-1/
dbus_files.files    = $$PWD/system.d/
 
dbus_services.path  = /usr/share/dbus-1/
dbus_services.files = $$PWD/system-services


SOURCES += main.cpp \
           pwm_manager.cpp         \
           ../../common/Adafruit_PWMServoDriver.cpp \
           ../../common/zoi2c.cpp \
           pwm_manager_interface.cpp

HEADERS += pwm_manager.h          \
           pwm_manager_interface.h	 \
           ../../common/zoi2c.h \
           ../../common/Adafruit_PWMServoDriver.h \
           ../common/pwm_plugin.h

target.path = /usr/bin/
INSTALLS += target 
INSTALLS += config_files
INSTALLS += dbus_files
INSTALLS += dbus_services

QMAKE_CLEAN += $$PWD/pwm_manager_interface.cpp \
               $$PWD/pwm_manager_interface.h   \
               $$PWD/com.robot.pwm_manager.xml \
               -r $$PWD/proxy/*

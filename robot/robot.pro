QT += core dbus
QT -= gui

CONFIG      += c++11
TARGET       = robot
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
INCLUDEPATH += $$(QT_SYSROOT)/usr/include/robot/


HEADERS += robotworker.h \
    positionthrd.h

SOURCES += main.cpp  \
           positionthrd.cpp \
           robotworker.cpp

target.path  = /usr/bin/
INSTALLS += target

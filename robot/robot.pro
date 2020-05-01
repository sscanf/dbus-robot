QT += core dbus
QT -= gui

CONFIG      += c++11
TARGET       = robot
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
INCLUDEPATH += $$(QT_SYSROOT)/usr/include/robot/

HEADERS += robotworker.h \
    pid.h \
    positionthrd.h \
    walkthread.h

SOURCES += main.cpp  \
           pid.cpp \
           positionthrd.cpp \
           robotworker.cpp \
           walkthread.cpp

target.path  = /usr/bin/
INSTALLS += target

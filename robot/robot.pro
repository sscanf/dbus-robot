QT += core dbus
QT -= gui

TARGET    = robot
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
#CONFIG    += c++11

#INCLUDEPATH += $$[QT_SYSROOT]/usr/include
#INCLUDEPATH += $$[QT_SYSROOT]
QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include

HEADERS += robotworker.h \
    manualcamerathrd.h \
    manualmotorsthrd.h \
    pid.h \
    positionthrd.h \
    walkthread.h

SOURCES += main.cpp  \
           manualcamerathrd.cpp \
           manualmotorsthrd.cpp \
           pid.cpp \
           positionthrd.cpp \
           robotworker.cpp \
           walkthread.cpp

target.path  = /usr/bin/
INSTALLS += target

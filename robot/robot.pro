QT += core dbus # core5compat
QT -= gui

TARGET    = robot
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
CONFIG    += c++11

#QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include
#QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CFLAGS += -Wno-cpp
#QMAKE_CXXFLAGS += -Wno-cpp

INCLUDEPATH += $$[QT_SYSROOT]/usr/lib/zone/includ
INCLUDEPATH += $$[QT_SYSROOT]/usr/include
INCLUDEPATH += $$[QT_SYSROOT]

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

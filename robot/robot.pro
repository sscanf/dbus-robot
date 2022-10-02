QT += core dbus
QT -= gui

TARGET    = robot
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
#CONFIG    += c++11

INCLUDEPATH += $$[QT_SYSROOT]/usr/include
INCLUDEPATH += ../common
#INCLUDEPATH += $$[QT_SYSROOT
QMAKE_CXXFLAGS += -std=c++0x

systemd_files.path  = /lib/systemd/
systemd_files.files = $$PWD/system/



HEADERS += robotworker.h \
    ../common/motiontasks_defs.h \
    manualcamerathrd.h \
    manualmotorsthrd.h \
    pid.h \
    positionthrd.h

SOURCES += main.cpp  \
           manualcamerathrd.cpp \
           manualmotorsthrd.cpp \
           pid.cpp \
           positionthrd.cpp \
           robotworker.cpp

target.path  = /usr/bin/
INSTALLS += target
INSTALLS += systemd_files

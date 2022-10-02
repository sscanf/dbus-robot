QT += core gui network qml quick quickwidgets dbus quick3d 3drender 3dcore 3dinput 3dlogic 3dextras 3danimation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++1y

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += common

SOURCES += main.cpp\
        common/itembase.cpp \
        ircamerawidget.cpp \
        mainwindow.cpp \
        powerwidget.cpp \
        sensorswidget.cpp \
        statuswidget.cpp \
        streamclientWidget.cpp \
        visionsettings.cpp

HEADERS  += mainwindow.h \
    ../common/robot.h \
    common/itembase.h \
    ircamerawidget.h \
    powerwidget.h \
    sensorswidget.h \
    statuswidget.h \
    streamclientWidget.h \
    visionsettings.h

FORMS    += mainwindow.ui \
    visionsettings.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    qml/Sensors_copy.qml

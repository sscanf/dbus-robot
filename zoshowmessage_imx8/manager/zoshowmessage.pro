
QT          += core qml quick
INCLUDEPATH += $$[QT_SYSROOT]/usr/lib/zone/include
TARGET       = zoshowmessage
TEMPLATE     = app


LIBS += -lpthread


target.path = /usr/bin/
RESOURCES += qml.qrc
SOURCES += main.cpp
INSTALLS += target


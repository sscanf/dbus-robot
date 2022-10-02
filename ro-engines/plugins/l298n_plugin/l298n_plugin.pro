QT += dbus
QT -= gui
#LIBS += -lsoc

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh l298n_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -r $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -Wno-cpp
QMAKE_CXXFLAGS += -Wno-cpp
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0


INCLUDEPATH += ../../common
INCLUDEPATH += ../../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
INCLUDEPATH += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(l298n-plugin)
DESTDIR      = plugins

HEADERS = \
          ../../../common/Adafruit_PWMServoDriver.h \
          ../../../common/zoi2c.h \
          ../../../common/motiontasks.h \
          l298n_worker_interface.h \
          l298n_factory.h          \
          l298n_worker.h \
          motiontasks.h

SOURCES  = \
          ../../../common/Adafruit_PWMServoDriver.cpp \
          ../../../common/zoi2c.cpp \
          l298n_worker_interface.cpp \
          l298n_worker.cpp           \
          l298n_factory.cpp \
          motiontasks.cpp

target.path = /usr/lib
INSTALLS += target

QMAKE_CLEAN += $$PWD/l298n_worker_interface.cpp       \
               $$PWD/l298n_worker_interface.h         \
               $$PWD/com.zitro.zone.l298n_manager.xml \
               -r $$PWD/proxy/*

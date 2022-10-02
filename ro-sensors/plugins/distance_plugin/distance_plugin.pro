QT += core dbus xml
QT -= gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh distance_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
#system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../../common/
INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(distance-plugin)
DESTDIR      = plugins
LIBS        += -lsoc

QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -Wno-cpp
QMAKE_CXXFLAGS += -Wno-cpp

sysroot_files.path    = $$[QT_SYSROOT]/etc/
sysroot_files.files   = $$PWD/robot/
sysroot_files.commands= cp $$config.files.files $$config_files.path

HEADERS = distance_worker_interface.h\
          distance_factory.h \
          distance_worker.h \
          ../../../common/imx6io.h \
          ../../../common/zoi2c.h \
          ../../../common/qsoc.h \
           enumsdbus.h

SOURCES  = distance_worker_interface.cpp\
           distance_factory.cpp \
           distance_worker.cpp \
           ../../../common/imx6io.cpp \
          ../../../common/qsoc.cpp \
           ../../../common/zoi2c.cpp

target.path = /usr/lib
INSTALLS += target

QMAKE_CLEAN += $$PWD/distance_worker_interface.cpp \
               $$PWD/distance_worker_interface.h   \
               $$PWD/com.robot.distance_manager.xml\
               -r $$PWD/proxy/*

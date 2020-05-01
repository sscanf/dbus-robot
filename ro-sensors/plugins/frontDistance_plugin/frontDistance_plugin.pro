QT += core dbus xml
QT -= gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh frontDistance_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
#system ($$quote(cp -a $${PWD}/proxy/* $$(QT_SYSROOT)/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../../common/
INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(frontDistance-plugin)
DESTDIR      = plugins
LIBS        += -lsoc

sysroot_files.path    = $$(QT_SYSROOT)/etc/
sysroot_files.files   = $$PWD/robot/
sysroot_files.commands= cp $$config.files.files $$config_files.path

HEADERS = frontDistance_worker_interface.h\
          frontDistance_factory.h         \
          frontDistance_worker.h          \
          ../../../common/imx6io.h \
          ../../../common/zoi2c.h

SOURCES  = frontDistance_worker_interface.cpp\
           frontDistance_worker.cpp          \
           frontDistance_factory.cpp         \
           ../../../common/imx6io.cpp \
           ../../../common/zoi2c.cpp

target.path = /usr/lib
INSTALLS += target

QMAKE_CLEAN += $$PWD/frontDistance_worker_interface.cpp \
               $$PWD/frontDistance_worker_interface.h   \
               $$PWD/com.robot.frontDistance_manager.xml\
               -r $$PWD/proxy/*

QT += dbus

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}
DEFINES += PLUGINS_PATH=\\\"/usr/lib\\\"



system ($$PWD/../tools/mkinterface.sh ina219_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(ina219-plugin)
DESTDIR      = plugins

sysroot_files.path    = $$(QT_SYSROOT)/etc/
sysroot_files.files   = $$PWD/robot/
sysroot_files.commands= cp $$config.files.files $$config_files.path

HEADERS = ina219_worker_interface.h   \
          ina219_factory.h            \
          ina219_worker.h

SOURCES  = ina219_worker_interface.cpp\
           ina219_worker.cpp          \
           ina219_factory.cpp

target.path = /usr/lib
INSTALLS += target

QMAKE_CLEAN += $$PWD/ina219_worker_interface.cpp       \
               $$PWD/ina219_worker_interface.h         \
               $$PWD/com.robot.ina219_manager.xml \
               -r $$PWD/proxy/*

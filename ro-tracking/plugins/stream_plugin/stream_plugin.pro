QT += dbus

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh stream_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$PWD/../tools/mkinterface.sh stream_worker)

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin debug
TARGET       = $$qtLibraryTarget(stream-plugin)
DESTDIR      = plugins
LIBS        += -lvlc
LIBS        += -L$$(OECORE_TARGET_SYSROOT)/usr/lib/arm-linux-gnueabihf/tegra/

dbus_proxy_files.path   = /usr/lib/robot/rotracking
dbus_proxy_files.files  = $$PWD/proxy
config_files.path       = /etc/
config_files.files      = $$PWD/robot/
resource_files.path     = /usr/lib/robot/rotracking
resource_files.files    = $$PWD/rc/

HEADERS = stream_worker_interface.h   \
          stream_factory.h            \
          stream_worker.h

SOURCES  = stream_worker_interface.cpp\
           stream_worker.cpp          \
           stream_factory.cpp

target.path = /usr/lib/
INSTALLS += target dbus_proxy_files resource_files

QMAKE_CLEAN += $$PWD/stream_worker_interface.cpp       \
               $$PWD/stream_worker_interface.h         \
               $$PWD/com.zitro.zone.stream_manager.xml \
               -r $$PWD/proxy/*

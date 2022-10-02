QT += dbus

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh mpu92_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../../common/
INCLUDEPATH += ../../common/
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(mpu92-plugin)
DESTDIR      = plugins

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -Wno-cpp
QMAKE_CXXFLAGS += -Wno-cpp

LIBS += -lsoc

HEADERS =   \
    ../../../common/imx6io.h \
    ../../../common/zoi2c.h \
    ../../../common/qsoc.h \
    mpu9250.h \
    mpu9250_registers.h \
    mpu92_factory.h \
    mpu92_worker.h \
    mpu92_worker_interface.h

SOURCES  =\
    mpu9250.cpp \
    mpu92_factory.cpp \
    ../../../common/imx6io.cpp \
    ../../../common/zoi2c.cpp \
    ../../../common/qsoc.cpp \
    mpu92_worker_interface.cpp \
    mpu92_worker.cpp

target.path = /usr/lib
INSTALLS += target

QMAKE_CLEAN += $$PWD/mpu950_worker_interface.cpp       \
               $$PWD/mpu950_worker_interface.h         \
               $$PWD/com.robot.mpu950_manager.xml \
               -r $$PWD/proxy/*

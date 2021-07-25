QT += dbus network
QT += gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh irtracker_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../../common
INCLUDEPATH += ../../common
INCLUDEPATH += ../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
#INCLUDEPATH += $$[QT_SYSROOT]/usr/include
QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(irtracker-plugin)
DESTDIR      = plugins
#LIBS        += -L$$(OECORE_TARGET_SYSROOT)/usr/lib/arm-linux-gnueabihf/tegra/

LIBS        += -lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc -lopencv_videoio  #-lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_vc_client -lmmal_util -lmmal_components -lraspicam

HEADERS = irtracker_worker_interface.h \
          irtracker_factory.h          \
          irtracker_worker.h \
          zoposircam.h \
          ../../../common/zoi2c.h \


SOURCES  = irtracker_worker_interface.cpp\
           irtracker_worker.cpp          \
           irtracker_factory.cpp \
           zoposircam.cpp \
           ../../../common/zoi2c.cpp \

target.path = /usr/lib/

INSTALLS += target #dbus_files dbus_services

QMAKE_CLEAN += $$PWD/irtracker_worker_interface.cpp       \
               $$PWD/irtracker_worker_interface.h         \
               $$PWD/com.robot.irtracker_manager.xml \
               -r $$PWD/proxy/*

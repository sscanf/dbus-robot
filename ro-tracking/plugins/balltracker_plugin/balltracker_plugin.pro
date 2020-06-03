QT += dbus network
QT += gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh balltracker_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += ../../lib
INCLUDEPATH += $$PWD/
DEPENDPATH  += $$PWD/
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(balltracker-plugin)
DESTDIR      = plugins
#LIBS        += -L$$(OECORE_TARGET_SYSROOT)/usr/lib/arm-linux-gnueabihf/tegra/

LIBS        += -lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc -lopencv_videoio  #-lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_vc_client -lmmal_util -lmmal_components -lraspicam

HEADERS = balltracker_worker_interface.h \
          balltracker_factory.h          \
          balltracker_worker.h \
          streamServer.h

SOURCES  = balltracker_worker_interface.cpp\
           balltracker_worker.cpp          \
           balltracker_factory.cpp \
           streamServer.cpp

target.path = /usr/lib/

INSTALLS += target #dbus_files dbus_services

QMAKE_CLEAN += $$PWD/balltracker_worker_interface.cpp       \
               $$PWD/balltracker_worker_interface.h         \
               $$PWD/com.robot.balltracker_manager.xml \
               -r $$PWD/proxy/*

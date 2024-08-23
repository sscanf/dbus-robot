QT += dbus network
QT += gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh facetracker_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/opencv4
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
#QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(facetracker-plugin)
DESTDIR      = plugins
#LIBS        += -L$$(OECORE_TARGET_SYSROOT)/usr/lib/arm-linux-gnueabihf/tegra/

LIBS        += -lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc -lopencv_videoio  #-lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_vc_client -lmmal_util -lmmal_components -lraspicam

HEADERS = facetracker_worker_interface.h \
          facetracker_factory.h          \
          facetracker_worker.h \
          streamServer.h

SOURCES  = facetracker_worker_interface.cpp\
           facetracker_worker.cpp          \
           facetracker_factory.cpp \
           streamServer.cpp

target.path = /usr/lib/

INSTALLS += target #dbus_files dbus_services

QMAKE_CLEAN += $$PWD/facetracker_worker_interface.cpp       \
               $$PWD/facetracker_worker_interface.h         \
               $$PWD/com.robot.facetracker_manager.xml \
               -r $$PWD/proxy/*

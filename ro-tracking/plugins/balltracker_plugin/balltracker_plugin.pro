QT += dbus network
QT += gui

VERSION = \\\"'01.00.00'\\\"
DEFINES += APP_VERSION=$${VERSION}

system ($$PWD/../tools/mkinterface.sh balltracker_worker)
system ($$quote(mkdir $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))
system ($$quote(cp -a $${PWD}/proxy/* $$[QT_SYSROOT]/usr/include/robot/$$escape_expand(\\n\\t)))

INCLUDEPATH += ../../common
INCLUDEPATH += ./plugins/common/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/opencv4
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
#QMAKE_CXXFLAGS += -I $$[QT_SYSROOT]/usr/include
TEMPLATE     = lib
CONFIG      += plugin
TARGET       = $$qtLibraryTarget(balltracker-plugin)
DESTDIR      = plugins
#LIBS        += -L$$(OECORE_TARGET_SYSROOT)/usr/lib/arm-linux-gnueabihf/tegra/

QMAKE_CXXFLAGS += -std=c++11

LIBS        += -lopencv_dnn     \
               -lopencv_dnn_objdetect     \
               -lopencv_core    \
               -lopencv_video   \
               -lopencv_videoio   \
               -lopencv_highgui \
               -lopencv_imgproc \
               -lopencv_face \
               -lopencv_cudaimgproc \
               -lopencv_cudawarping \
               -lopencv_cudacodec \
               -lopencv_cudaobjdetect \
               -lopencv_objdetect \
               -lnvcuvid

#-lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_vc_client -lmmal_util -lmmal_components -lraspicam

HEADERS = balltracker_worker_interface.h \
          balltracker_factory.h          \
          balltracker_worker.h \
          facetracker.h \
          streamServer.h

SOURCES  = balltracker_worker_interface.cpp\
           balltracker_worker.cpp          \
           balltracker_factory.cpp \
           facetracker.cpp \
           streamServer.cpp

target.path = /usr/lib/

INSTALLS += target #dbus_files dbus_services

QMAKE_CLEAN += $$PWD/balltracker_worker_interface.cpp       \
               $$PWD/balltracker_worker_interface.h         \
               $$PWD/com.robot.balltracker_manager.xml \
               -r $$PWD/proxy/*

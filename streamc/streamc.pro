#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T14:15:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = streamc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        streamclientWidget.cpp

HEADERS  += mainwindow.h \
    streamclientWidget.h

FORMS    += mainwindow.ui

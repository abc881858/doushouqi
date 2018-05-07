#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T21:48:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logviewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

SOURCES += main.cpp\
    mainwindow.cpp \
    createtable.cpp \
    leftwidget.cpp \
    logdata.cpp \
    chartwidget.cpp \
    qchartviewer.cpp

HEADERS += mainwindow.h \
    createtable.h \
    leftwidget.h \
    logdata.h \
    chartwidget.h \
    qchartviewer.h \
    duration.h

QMAKE_RPATHDIR += ../lib

INCLUDEPATH += ../include

#ChartDirector lib
LIBS += -L../lib -lchartdir

#QtAV lib
LIBS += ../lib/libQtAV.so
LIBS += ../lib/libQtAVWidgets.so

#FFmpeg lib
LIBS += ../lib/libavcodec.so.57
LIBS += ../lib/libavdevice.so.57
LIBS += ../lib/libavfilter.so.6
LIBS += ../lib/libavformat.so.57
LIBS += ../lib/libavresample.so.3
LIBS += ../lib/libavutil.so.55
LIBS += ../lib/libswresample.so.2
LIBS += ../lib/libswscale.so.4

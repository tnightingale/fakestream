#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T20:16:24
#
#-------------------------------------------------

QT       += core gui

CONFIG   += mobility
MOBILITY += multimedia

TARGET = audio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bufferloader.cpp \
    threadsafebuffer.cpp

HEADERS  += mainwindow.h \
    bufferloader.h \
    threadsafebuffer.h

FORMS    += mainwindow.ui

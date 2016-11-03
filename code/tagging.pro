#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T15:52:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tagging
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mytagbutton.cpp \
    tagmanager.cpp \
    tagselectorwidget.cpp \
    flowlayout.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    mytagbutton.h \
    tagmanager.h \
    tagselectorwidget.h \
    flowlayout.h \
    dbmanager.h

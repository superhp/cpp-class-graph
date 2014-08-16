#-------------------------------------------------
#
# Project created by QtCreator 2014-06-01T15:55:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CDui
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           search.cpp \
           visitortraversal.cpp

HEADERS  += mainwindow.h \
            search.hpp
            visitortraversal.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/lib/CDuilib/include

LIBS += -L/usr/lib/CDuilib/lib -lrose
LIBS += -Wl,-rpath=/usr/lib/CDuilib/lib

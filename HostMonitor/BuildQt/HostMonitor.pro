#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T16:40:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloGL
TEMPLATE = app
LIBS+=../UIcode/libUIcode.a
LIBS+=../../../GuiLite/libGuiLite.a
LIBS+=-ldl
INCLUDEPATH+=../UIcode/core_include
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

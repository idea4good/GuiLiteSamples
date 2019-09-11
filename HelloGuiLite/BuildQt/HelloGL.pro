#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T16:40:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloGuiLite
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp\
        ../UIcode/helloGL.cpp\
        ../UIcode/resource/desktop_bmp.cpp\
        ../UIcode/resource/start_icon_bmp.cpp\
        ../UIcode/resource/start_icon_click_bmp.cpp\
        ../UIcode/resource/start_menu_bmp.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

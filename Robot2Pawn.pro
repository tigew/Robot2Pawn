#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T14:49:24
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Robot2Pawn
TEMPLATE = app
win32:RC_ICONS += favicon.ico


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

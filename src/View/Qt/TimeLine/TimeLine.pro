#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T16:03:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeLine
TEMPLATE = app

INCLUDEPATH += ../../..

SOURCES += main.cpp\
    ../../../DAL/DataAcces.cpp \
    ../../../DAL/sqlite3.c \
    ../../../POCO/Fact.cpp \
    ../../../POCO/TimeHour.cpp \
    MainWin.cpp \
    FactTableModel.cpp \
    FactDialog.cpp

HEADERS  += ../../../DAL/DataAcces.h \
    ../../../DAL/sqlite3.h \
    ../../../POCO/Fact.h \
    ../../../POCO/TimeHour.h \
    MainWin.h \
    FactTableModel.h \
    FactDialog.h

FORMS += \
    MainWin.ui \
    FactDialog.ui


#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T16:03:50
#
#-------------------------------------------------

QT       += core gui quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeLine
TEMPLATE = app

INCLUDEPATH += ../../..

SOURCES += main.cpp\
    ../../../DAL/DataAcces.cpp \
    ../../../DAL/sqlite3.c \
    ../../../POCO/Fact.cpp \
    ../../../POCO/TimeHour.cpp \
    mainwin.cpp \
    facttablemodel.cpp

HEADERS  += ../../../DAL/DataAcces.h \
    ../../../DAL/sqlite3.h \
    ../../../POCO/Fact.h \
    ../../../POCO/TimeHour.h \
    mainwin.h \
    facttablemodel.h

FORMS += \
    mainwin.ui

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DAL/DataAcces.cpp \
    DAL/sqlite3.c \
    POCO/ADateTime.cpp \
    POCO/Fact.cpp \
    POCO/ACategory.cpp \
    POCO/AConfigManager.cpp \
    POCO/Facts.cpp \
    View/AlxColors.cpp \
    View/CategoryDialog.cpp \
    View/FactDialog.cpp \
    View/FactSortFilterProxyModel.cpp \
    View/FactTableModel.cpp \
    View/MainWin.cpp \
    View/main.cpp

HEADERS += \
    DAL/DataAcces.h \
    DAL/sqlite3.h \
    POCO/ADateTime.h \
    POCO/Fact.h \
    POCO/ACategory.h \
    POCO/AConfigManager.h \
    POCO/Facts.h \
    View/AlxColors.h \
    View/CategoryDialog.h \
    View/FactDialog.h \
    View/FactSortFilterProxyModel.h \
    View/FactTableModel.h \
    View/MainWin.h

FORMS += \
    View/CategoryDialog.ui \
    View/MainWin.ui \
    View/factdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    View/Qt.zip

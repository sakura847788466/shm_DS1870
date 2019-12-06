#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T08:37:15
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
WARNINGS += -Wall

TARGET = IDGenerator
TEMPLATE = app

# set appication icon
RC_FILE += app.rc


PRECOMPILED_HEADER = preCompiled.h

SOURCES += main.cpp\
        mainwindow.cpp \
    dashboardpage.cpp \
    generatorpage.cpp \
    historypage.cpp \
    idworker.cpp \
    generatingpage.cpp \
    mymodel.cpp \
    iduploader.cpp \
    configdlg.cpp

HEADERS  += mainwindow.h \
    dashboardpage.h \
    precompiled.h \
    generatorpage.h \
    historypage.h \
    idworker.h \
    generatingpage.h \
    mymodel.h \
    idstructs.h \
    iduploader.h \
    configdlg.h

RESOURCES += \
    resources.qrc

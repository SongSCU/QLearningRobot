#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T22:34:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GridWorld
TEMPLATE = vcapp


SOURCES += main.cpp\
        cmain_frm.cpp \
    crect_item.cpp \
    Evironment.cpp \
    Map.cpp \
    QLearningRobot.cpp

HEADERS  += cmain_frm.h \
    baseDataStruct.h \
    crect_item.h \
    Evironment.h \
    Map.h \
    QLearningRobot.h \
    unistd.h

FORMS    += cmain_frm.ui

RESOURCES += \
    res.qrc

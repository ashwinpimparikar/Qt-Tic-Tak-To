#-------------------------------------------------
#
# Project created by QtCreator 2019-08-07T17:12:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TikTakTo
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    diagramitem.cpp \
    diagramscene.cpp

HEADERS  += dialog.h \
    diagramitem.h \
    diagramscene.h

FORMS    += dialog.ui

RESOURCES += \
    images.qrc

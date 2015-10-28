#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T15:26:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = glutTest
TEMPLATE = app

INCLUDEPATH += freeglut\include \

LIBS += -L$$PWD\freeglut\lib\x64 \
-lfreeglut
-lfreeglut_static

SOURCES += main.cpp\
        mainwindow.cpp \
    glframework.cpp \
    coordinatecalculator.cpp

HEADERS  += mainwindow.h \
    glframework.h \
    coordinatecalculator.h

FORMS    += mainwindow.ui

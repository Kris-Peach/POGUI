#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T19:13:51
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

TARGET = tst_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_unittest.cpp \
    yantranslate.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    yantranslate.h

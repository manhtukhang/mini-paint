#! [0]
QT += widgets
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets printsupport
    DEFINES += HAVE_QT5
}

TARGET = minipaint-v1.0
VERSION = 1.0
TEMPLATE = app


#DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

HEADERS        = interfaces.h \
                 mainwindow.h \
                 paintarea.h \
                 plugindialog.h
SOURCES        = main.cpp \
                 mainwindow.cpp \
                 paintarea.cpp \
                 plugindialog.cpp

LIBS           = -L$$PWD -lbasictools

if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
   mac:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)_debug
   win32:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)d
}
#! [0]

# install
#target.path = ../
#INSTALLS += target

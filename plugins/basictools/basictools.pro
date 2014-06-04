#/********************************************
# * Mini Paint                               *
# * Copyleft (Ɔ) 2014 - Mini Paint           *
# * https://github.com/manhtuvjp/mini-paint  *
# ********************************************/


TEMPLATE      = lib
CONFIG       += plugin static
QT           += widgets

INCLUDEPATH  += ../..
HEADERS       = basictoolsplugin.h
SOURCES       = basictoolsplugin.cpp

TARGET        = $$qtLibraryTarget(basictools)

OBJECTS_DIR   = ../build
MOC_DIR       = ../build
UI_DIR 		  = ../build
DESTDIR       = ../../

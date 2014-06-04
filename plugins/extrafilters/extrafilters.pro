#/********************************************
# * Mini Paint                               *
# * Copyleft (Ɔ) 2014 - Mini Paint           *
# * https://github.com/manhtuvjp/mini-paint  *
# ********************************************/


TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets

INCLUDEPATH  += ../..
HEADERS       = extrafiltersplugin.h
SOURCES       = extrafiltersplugin.cpp

TARGET        = $$qtLibraryTarget(extrafilters)

OBJECTS_DIR   = ../build
MOC_DIR       = ../build
UI_DIR 		  = ../build
DESTDIR       = ../../

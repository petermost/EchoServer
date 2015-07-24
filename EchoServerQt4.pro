#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T12:17:52
#
#-------------------------------------------------

TARGET = EchoServerQt4

QT       += core network
QT       -= gui

CONFIG   += c++11 console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
	EchoServerQt4.cpp \
	mainQt4.cpp \
	EchoClientQt4.cpp

HEADERS += \
	EchoServerQt4.hpp \
	EchoClientQt4.hpp

DISTFILES += \
	README.md

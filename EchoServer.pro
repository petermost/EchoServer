#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T12:17:52
#
#-------------------------------------------------

TARGET = EchoServer

QT       += core network
QT       -= gui

CONFIG   += c++11 console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
	EchoServer.cpp

HEADERS += \
	EchoServer.hpp

DISTFILES += \
	README.md

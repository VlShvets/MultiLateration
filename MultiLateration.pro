#-------------------------------------------------
#
# Project created by QtCreator 2014-07-24T20:00:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix|win32: LIBS += -L$$PWD/../../PTPV/Library/ -lGrapher2D
INCLUDEPATH += $$PWD/../../PTPV/Grapher2D

TARGET = MultiLateration
TEMPLATE = app

SOURCES += main.cpp\
    settinglok.cpp \
    settingroc.cpp \
    settingtotal.cpp \
    painter.cpp \
    multilateration.cpp

HEADERS  += \
    settinglok.h \
    settingroc.h \
    settingtotal.h \
    painter.h \
    multilateration.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

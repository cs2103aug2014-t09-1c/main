#-------------------------------------------------
#
# Project created by QtCreator 2014-09-21T14:53:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = t01-1c_ui
TEMPLATE = app

#CONFIG += static


SOURCES += main.cpp\
        mainwindow.cpp \
    cmenubar.cpp \
    ccombobox.cpp \
    ccompleter.cpp \
    clineedit.cpp \
    ctable.cpp \
    cprogressbar.cpp

HEADERS  += mainwindow.h \
    cmenubar.h \
    ccombobox.h \
    ccompleter.h \
    clineedit.h \
    ctable.h \
    cprogressbar.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    resource.qrc

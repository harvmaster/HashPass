#-------------------------------------------------
#
# Project created by QtCreator 2014-09-25T19:49:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hashpass
TEMPLATE = app

win32 {
    CONFIG += static
}

SOURCES += main.cpp\
        MainDialog.cpp

HEADERS  += MainDialog.h

FORMS    += MainDialog.ui

OTHER_FILES += \
    hashpass.desktop

target.path = /usr/bin

desktop.path = /usr/share/applications/
desktop.files += hashpass.desktop

INSTALLS += target desktop

RESOURCES += \
    resources.qrc

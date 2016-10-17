QT += core serialport testlib
QT += gui widgets

TARGET = IcebergNOGUI
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    mainwindow.cpp \
    joystick.cpp \
    motor.cpp \
    settings.cpp \
    dialog.cpp

HEADERS += \
    server.h \
    messages.h \
    mainwindow.h \
    joystick.h \
    motor.h \
    settings.h \
    dialog.h

DEFINES += SFML_STATIC

LIBS += -L$$PWD/SFML-win32/lib

INCLUDEPATH += $$PWD/SFML-win32/include

DEPENDPATH += $$PWD/SFML-win32/include

CONFIG(release, debug|release): LIBS += -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-window-d

FORMS += \
    mainwindow.ui \
    dialog.ui

QT += core serialport testlib
QT += gui widgets
QT += svg

TARGET = IcebergNOGUI
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    mainwindow.cpp \
    joystick.cpp \
    settings.cpp \
    qfi_PFD.cpp

HEADERS += \
    server.h \
    messages.h \
    mainwindow.h \
    joystick.h \
    settings.h \
    qfi_PFD.h

DEFINES += SFML_STATIC

win32:contains(QMAKE_HOST.arch, x86_64) {
    LIBS += -L$$PWD/SFML-win64/lib

    INCLUDEPATH += $$PWD/SFML-win64/include

    DEPENDPATH += $$PWD/SFML-win64/include
} else {
    LIBS += -L$$PWD/SFML-win32/lib

    INCLUDEPATH += $$PWD/SFML-win32/include

    DEPENDPATH += $$PWD/SFML-win32/include
}

LIBS += -L$$PWD/SFML-win32/lib

INCLUDEPATH += $$PWD/SFML-win32/include

DEPENDPATH += $$PWD/SFML-win32/include

CONFIG(release, debug|release): LIBS += -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-window-d

FORMS += \
    mainwindow.ui \
    WidgetPFD.ui

RESOURCES += \
    qfi.qrc

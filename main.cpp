#include <QApplication>
#include "server.h"
#include "mainwindow.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;

    Server server;

    Settings settings;

    server.motors = settings.motors;
    mainWindow.motors = settings.motors;

    mainWindow.init();

    //QObject::connect(&mainWindow, SIGNAL(newValues(int*)), &server, SLOT(setNewValues(int*)));
    QObject::connect(&mainWindow, SIGNAL(changeControl(bool)), &server, SLOT(setControl(bool)));
    QObject::connect(&mainWindow, SIGNAL(tryConnect()), &server, SLOT(connect_com()));
    QObject::connect(&mainWindow, SIGNAL(disconnect()), &server, SLOT(disconnect_com()));
    QObject::connect(&mainWindow, SIGNAL(changeMotorSetting(int, QString, bool)),
                     &settings, SLOT(changeMotorSetting(int, QString, bool)));


    mainWindow.show();
    return a.exec();
}

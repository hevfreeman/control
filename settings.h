#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

#include <QObject>
#include <QString>
#include <QFile>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "motor.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    Motor* motors;

private:
    void initialize();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    bool loadFromJSONFile();
    bool saveToJSONFIle() const;
signals:

public slots:
    void changeMotorSetting(int slot, QString motorID, bool inverse);
};

#endif // SETTINGS_H

#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    motors = new Motor[8];
    initialize();
    loadFromJSONFile();
}

void Settings::initialize() {
    for (int i = 0; i < 8; ++i) {
        motors[i].code = Motor::MotorCode::VF;
        motors[i].adress = i;
        motors[i].inverse = false;
        motors[i].enabled = true;
        motors[i].speed = 0;
        motors[i].k_backward = 1.;
        motors[i].k_forward = 1.;
    }
}

void Settings::read(const QJsonObject &json)
{
    QJsonArray motorArray = json["motors"].toArray();
    for (int i = 0; i < motorArray.size(); ++i) {
        QJsonObject motorObject = motorArray[i].toObject();

        if (i == motorObject["slot"].toInt()) {
            std::cout << "Parsing slot " << i << " settings..." << std::endl;
            motors[i].setCode(motorObject["code"].toString());
            std::cout << "code = " << motors[i].getCode().toStdString() << std::endl;
            motors[i].inverse = motorObject["inverse"].toBool();
            std::cout << "inverse = " << motors[i].inverse << std::endl;
            motors[i].enabled = motorObject["enabled"].toBool();
            std::cout << "enabled = " << motors[i].enabled << std::endl;
            motors[i].k_backward = motorObject["k_backward"].toDouble();
            std::cout << "k_backward = " << motors[i].k_backward << std::endl;
            motors[i].k_forward = motorObject["k_forward"].toDouble();
            std::cout << "k_forward = " << motors[i].k_forward << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << "Wrong slot order in JSON file" << std::endl;
            std::cout << "Wrong slot order in JSON file" << std::endl;
        }

    }
}

void Settings::write(QJsonObject &json) const
{
    QJsonArray motorArray;

    for (int i = 0; i < 8; ++i) {
        QJsonObject motorObject;

        motorObject["slot"] = i;
        motorObject["code"] = motors[i].getCode();
        motorObject["inverse"] = motors[i].inverse;
        motorObject["enabled"] = motors[i].enabled;
        motorObject["k_backward"] = motors[i].k_backward;
        motorObject["k_forward"] = motors[i].k_forward;

        motorArray.append(motorObject);
    }

    json["motors"] = motorArray;
}


bool Settings::loadFromJSONFile() {
    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
    std::cout << "Settings loaded" << std::endl;
    return true;
}


bool Settings::saveToJSONFIle() const{
    QFile saveFile("save.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        std::cout << "Couldn't open save file." << std::endl;
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson(QJsonDocument::Indented));
    std::cout << "Settings saved" << std::endl;
    return true;
}

void Settings::changeMotorSetting(int slot, QString motorID, bool inverse) {
    //motors[slot].setCode(motorID);
    //motors[slot].inverse = inverse;

    saveToJSONFIle();
    loadFromJSONFile();
    std::cout << "Motor " << motorID.toStdString() << " is now binded to " << slot << " slot"
              << (inverse?" ":" not ") << "inverse" << std::endl;
}

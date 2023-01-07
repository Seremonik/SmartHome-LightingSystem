#include "SaveSystem.h"

SaveSystem::SaveSystem()
{
}

SaveSystem::~SaveSystem()
{
}

bool SaveSystem::isPinOn(int pin)
{
    if (isInitialized)
    {
        char fileName[2 + sizeof(char)];
        sprintf(fileName, "%d", pin);
        return SD.exists(fileName);
    }
    return false;
}

void SaveSystem::SavePinState(int pin, bool isOn)
{
    char fileName[2 + sizeof(char)];
    sprintf(fileName, "%d", pin);

    if (isOn)
    {
        File file = SD.open(fileName, FILE_WRITE);
        file.close();
    }
    else
    {
        SD.remove(fileName);
    }
}

void SaveSystem::Initialize()
{
    Serial.println("Initializing SD card...");
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);

    if (!SD.begin(4))
    {
        //TODO Raise some flag and inform MQTT broker
        Serial.println("initialization failed!");
        return;
    }
    isInitialized = true;
    Serial.println("SD Initialization succeed");
}
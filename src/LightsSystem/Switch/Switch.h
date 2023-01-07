#ifndef Switch_H
#define Switch_H

#include "SaveSystem/SaveSystem.h"
#include "MQTTSystem/MQTTSystem.h"
#include "../Button/Button.h"

class Switch
{
protected:
    SaveSystem *saveSystem;
    MQTTSystem *mqttSystem;

    int *buttonPins;
    int *outputPins;

    int buttonsCount;
    int outputCount;

    Button *buttons;

public:
    Switch(int *buttonPins, int buttonsCount, int *outputPin, int outputCount);
    ~Switch();
    virtual void Update();
    virtual void Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem);
    virtual void ReceivedMessege(String &topic, String &payload);
};

#endif
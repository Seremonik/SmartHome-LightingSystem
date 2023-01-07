#ifndef LightSystem_H
#define LightSystem_H

#include "LightSwitch/LightSwitch.h"
#include "ShutterSwitch/ShutterSwitch.h"
#include "Arduino.h"
#include "SaveSystem/SaveSystem.h"
#include "MQTTSystem/MQTTSystem.h"
#include <Utils/util.h>

class LightsSystem
{
private:
    SaveSystem *saveSystem;
    MQTTSystem *mqttSystem;
    static void MessageReceived(String &topic, String &payload);

public:

    LightsSystem(SaveSystem *saveSystem, MQTTSystem *mqttSystem);
    ~LightsSystem();
    void Update();
    void Initialize();
    void ProcessButton(LightSwitch *lightButton);
};

#endif
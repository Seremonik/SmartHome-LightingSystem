#ifndef LightSwitch_H
#define LightSwitch_H

#include "../Switch/Switch.h"

class LightSwitch : public Switch
{
private:
    bool buttonIsPressed;
    SaveSystem *saveSystem;

public:
    String mqttTopic;

    bool previousRegisteredState = false;
    bool currentState = false; //
    bool isButtonHold = false;
    bool isOutputOn = false;
    unsigned long clickMillis; //time when button was pressed

    LightSwitch(int *buttonPins, int buttonsCount, int *outputPin, int outputCount, String mqttTopic);
    ~LightSwitch();
    void Update();
    void Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem);
    void ReceivedMessege(String &topic, String &payload);

    void SwitchLight();
    void TurnOnLight();
    void TurnOffLight();
};

#endif
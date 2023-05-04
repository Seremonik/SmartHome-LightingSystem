#ifndef ShutterSwitch_H
#define ShutterSwitch_H

#include "../Switch/Switch.h"

class ShutterSwitch : public Switch
{

private:
    String mqttTopic;
    bool isButtonUpPressed = false;
    bool isButtonDownPressed = false;
    bool isOnAuto = false;
    unsigned int autoCloseDurationMiliseconds;
    unsigned long clickTimestamp;
    unsigned long automaticHoldTimestamp;

public:
    ShutterSwitch(int *buttonPins, int *outputPins, unsigned int autoCloseDurationMiliseconds, String mqttTopic);
    void Update();
    void Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem);
    void ReceivedMessege(String &topic, String &payload);

    void ReleaseButton();
    void GoUp();
    void GoDown();
    void Stop();
};

#endif
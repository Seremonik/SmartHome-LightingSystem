#include "LightSwitch.h"

LightSwitch::LightSwitch(int *buttonPins,
                         int buttonsCount,
                         int *outputPin,
                         int outputCount,
                         String mqttTopic) : Switch(buttonPins, buttonsCount, outputPin, outputCount)
{
    this->mqttTopic = mqttTopic;
}

LightSwitch::~LightSwitch()
{
}

void LightSwitch::Update()
{
    for (int i = 0; i < buttonsCount; i++)
    {
        buttons[i].Update();
        if (buttons[i].HasChangedSate(buttonIsPressed))
        {
            if (buttonIsPressed)
            {
                SwitchLight();
            }
        }
    }
}

void LightSwitch::Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem)
{
    Switch::Initialize(saveSystem, mqttSystem);

    isOutputOn = saveSystem->isPinOn(outputPins[0]);

    for (int i = 0; i < outputCount; i++)
    {
        digitalWrite(outputPins[i], !isOutputOn);
    }
}

void LightSwitch::ReceivedMessege(String &topic, String &payload)
{
    if (topic.compareTo(mqttTopic) == 0)
    {
        Serial.println("incoming from MQTT!: " + topic + " - " + payload);
        if (payload.compareTo("1") == 0)
        {
            TurnOnLight();
        }
        else if (payload.compareTo("0") == 0)
        {
            TurnOffLight();
        }
    }
}

void LightSwitch::TurnOnLight()
{
    if (!isOutputOn)
    {
        SwitchLight();
    }
}

void LightSwitch::TurnOffLight()
{
    if (isOutputOn)
    {
        SwitchLight();
    }
}

void LightSwitch::SwitchLight()
{
    isOutputOn = !isOutputOn;
    for (int i = 0; i < outputCount; i++)
    {
        digitalWrite(outputPins[i], !isOutputOn);
    }

    saveSystem->SavePinState(outputPins[0], isOutputOn);
    mqttSystem->SetValue(mqttTopic, isOutputOn ? "1" : "0");
}

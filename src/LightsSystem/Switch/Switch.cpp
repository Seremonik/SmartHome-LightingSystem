#include "Switch.h"

Switch::Switch(int *buttonPins, int buttonsCount, int *outputPin, int outputCount)
{
    this->buttonPins = buttonPins;
    this->buttonsCount = buttonsCount;
    this->outputPins = outputPin;
    this->outputCount = outputCount;
}

Switch::~Switch()
{
    delete (buttons);
}

void Switch::Update()
{
}

void Switch::ReceivedMessege(String &topic, String &payload)
{
}

void Switch::Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem)
{
    this->saveSystem = saveSystem;
    this->mqttSystem = mqttSystem;
    buttons = new Button[buttonsCount];

    for (int i = 0; i < buttonsCount; i++)
    {
        buttons[i].Initialize(buttonPins[i]);
    }

    for (int i = 0; i < outputCount; i++)
    {
        pinMode(outputPins[i], OUTPUT);
        digitalWrite(outputPins[i], true); //to prevent quick flash on reset.
    }
}
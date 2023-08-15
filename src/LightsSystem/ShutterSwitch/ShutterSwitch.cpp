#include "ShutterSwitch.h"
#include"Config.h"

//Button pins order: {UP,DOWN},  OutputPins order:{UP,DOWN}
ShutterSwitch::ShutterSwitch(int *buttonPins,
                             int *outputPins, 
                             unsigned int autoCloseDurationMiliseconds,
                             String mqttTopic) : Switch(buttonPins, 2, outputPins, 2)
{
    this->mqttTopic = mqttTopic;
    this->stopMqttTopic = mqttTopic + "/stop";
    this->upMqttTopic = mqttTopic + "/up";
    this->downMqttTopic = mqttTopic + "/down";
    this->autoCloseDurationMiliseconds = autoCloseDurationMiliseconds;
}

void ShutterSwitch::Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem)
{
    Switch::Initialize(saveSystem, mqttSystem);
}

void ShutterSwitch::ReceivedMessege(String &topic, String &payload)
{
    if (topic.compareTo(stopMqttTopic) == 0)
    {
        Stop();
    }
    if (topic.compareTo(upMqttTopic) == 0)
    {
        GoUp();
        isOnAuto = true;
        automaticHoldTimestamp = millis();
    }
    if (topic.compareTo(downMqttTopic) == 0)
    {
        GoDown();
        isOnAuto = true;
        automaticHoldTimestamp = millis();
    }
}

void ShutterSwitch::Update()
{
    if (!isButtonDownPressed)
    {
        buttons[0].Update();
        if (buttons[0].IsPressed != isButtonUpPressed)
        {
            isButtonUpPressed = buttons[0].IsPressed;
            if (isButtonUpPressed)
            {
                GoUp();
            }
            else
            {
                ReleaseButton();
            }
            clickTimestamp = millis();
        }
    }
    if (!isButtonUpPressed)
    {
        buttons[1].Update();
        if (buttons[1].IsPressed != isButtonDownPressed)
        {
            isButtonDownPressed = buttons[1].IsPressed;
            if (isButtonDownPressed)
            {
                GoDown();
            }
            else
            {
                ReleaseButton();
            }
            clickTimestamp = millis();
        }
    }
    //if was going automatic for X second then stop
    if (isOnAuto)
    {
        if (isButtonUpPressed || isButtonDownPressed || TimePast(automaticHoldTimestamp, autoCloseDurationMiliseconds))
        {
            Stop();
        }
    }
}

void ShutterSwitch::GoUp()
{
    isOnAuto = false;
    digitalWrite(outputPins[1], true);
    digitalWrite(outputPins[0], false);
}

void ShutterSwitch::GoDown()
{
    isOnAuto = false;
    digitalWrite(outputPins[0], true);
    digitalWrite(outputPins[1], false);
}

void ShutterSwitch::ReleaseButton()
{
    //if button was hold for Xs then dont stop
    if (TimePast(clickTimestamp, ShutterButtonHoldTimeMiliseconds))
    {
        isOnAuto = true;
        automaticHoldTimestamp = millis();
    }
    else
    {
        Stop();
    }
}

void ShutterSwitch::Stop()
{
    isOnAuto = false;
    automaticHoldTimestamp = millis();
    digitalWrite(outputPins[0], true); // true means its off
    digitalWrite(outputPins[1], true);
}
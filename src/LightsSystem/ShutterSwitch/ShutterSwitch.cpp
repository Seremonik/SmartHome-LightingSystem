#include "ShutterSwitch.h"
#include"Config.h"

//Button pins order: {UP,DOWN},  OutputPins order:{UP,DOWN}
ShutterSwitch::ShutterSwitch(int *buttonPins,
                             int *outputPins, 
                             unsigned int autoCloseDurationMiliseconds,
                             String mqttTopic) : Switch(buttonPins, 2, outputPins, 2)
{
    this->mqttTopic = mqttTopic;
    this->stateTopic = mqttTopic + "/state";
    this->commandTopic = mqttTopic + "/set";
    this->autoCloseDurationMiliseconds = autoCloseDurationMiliseconds;
}

void ShutterSwitch::Initialize(SaveSystem *saveSystem, MQTTSystem *mqttSystem)
{
    Switch::Initialize(saveSystem, mqttSystem);
}

void ShutterSwitch::ReceivedMessege(String &topic, String &payload)
{
    if (topic.compareTo(commandTopic) != 0)
    {
        return;
    }
    
    if(payload == "OPEN")
    {
        GoUp();
        isOnAuto = true;
        automaticHoldTimestamp = millis();
    }
    if(payload == "CLOSE")
    {
        GoDown();
        isOnAuto = true;
        automaticHoldTimestamp = millis();
    }
    if(payload == "STOP")
    {
        Stop();
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
    // if (isOnAuto)
    // {
    //     if (isButtonUpPressed || isButtonDownPressed || TimePast(automaticHoldTimestamp, autoCloseDurationMiliseconds))
    //     {
    //         //Stop();
    //     }
    // }
}

void ShutterSwitch::GoUp()
{
    mqttSystem->SetValue(stateTopic, "opening");
    isOnAuto = false;
    digitalWrite(outputPins[1], true);
    digitalWrite(outputPins[0], false);
}

void ShutterSwitch::GoDown()
{
    mqttSystem->SetValue(stateTopic, "closing");
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
    mqttSystem->SetValue(stateTopic, "stopped");
    isOnAuto = false;
    automaticHoldTimestamp = millis();
    digitalWrite(outputPins[0], true); // true means its off
    digitalWrite(outputPins[1], true);
}
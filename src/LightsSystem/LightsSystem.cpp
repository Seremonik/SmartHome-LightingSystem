#include "LightsSystem.h"
#include "Button/ButtonsMap.h"

LightsSystem::LightsSystem(SaveSystem *saveSystem, MQTTSystem *mqttSystem)
{
    this->saveSystem = saveSystem;
    this->mqttSystem = mqttSystem;
}

LightsSystem::~LightsSystem()
{
}

void LightsSystem::Update()
{
    //Loops over existing buttons and check if state changed
    for (int i = 0; i < LightSwitchesCount; i++)
    {
        LightSwitches[i]->Update();
    }
}

void LightsSystem::Initialize()
{
    mqttSystem->mqttClient.onMessage(MessageReceived);

    Serial.println("Initializing Lights...");

    for (int i = 0; i < LightSwitchesCount; i++)
    {
        LightSwitches[i]->Initialize(saveSystem, mqttSystem);
    }
    Serial.println("Lights initialized");
}

void LightsSystem::MessageReceived(String &topic, String &payload)
{
    Serial.println("MQTT incoming: " + topic + " - " + payload);
    for (int i = 0; i < LightSwitchesCount; i++)
    {
        LightSwitches[i]->ReceivedMessege(topic, payload);
    }
}
#include <Arduino.h>
#include <avr/wdt.h>
#include <SaveSystem/SaveSystem.h>
#include <MQTTSystem/MQTTSystem.h>
#include "LightsSystem/Switch/Switch.h"
#include <LightsSystem/LightsSystem.h>
#include "LightsSystem/Button/Button.h"

SaveSystem saveSystem;
MQTTSystem mqttSystem;
LightsSystem lightsSystem(&saveSystem, &mqttSystem);

void setup()
{
  Serial.begin(9600);

  Serial.println("Reset!");
  saveSystem.Initialize();
  lightsSystem.Initialize();
  mqttSystem.InitializeEthernet();

  wdt_enable(WDTO_8S);
}

void loop()
{
  wdt_reset();

  lightsSystem.Update();
  mqttSystem.Update();
}
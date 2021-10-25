#include <Arduino.h>
#include <avr/wdt.h>
#include <SaveSystem/SaveSystem.h>
#include <MQTTSystem/MQTTSystem.h>

SaveSystem saveSystem;
MQTTSystem mqttSystem;

void setup()
{
  Serial.begin(9600);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  saveSystem.Initialize();
  mqttSystem.InitializeEthernet();

  wdt_enable(WDTO_4S);
}

void loop()
{
  wdt_reset();

  mqttSystem.Update();
  // put your main code here, to run repeatedly:
}
#ifndef MQTTSystem_H
#define MQTTSystem_H

#include <MQTT.h>
#include <Arduino.h>
#include <Ethernet.h>
#include <Utils/util.h>

extern byte mac[];
extern const char *server;
extern const int port;
extern const char *clientID;
extern const char *username;
extern const char *password;

class MQTTSystem
{
private:
    bool isMqttInitialized = false;
    bool isEthernetInitialized = false;
    unsigned long initializationTime = 0;

    EthernetClient ethClient;
    static void SubscribeReceive(String &topic, String &payload);
    void InitializeMQTT();

public:
    MQTTClient mqttClient;
    MQTTSystem();
    ~MQTTSystem();
    void InitializeEthernet();
    void Update();
    void SetValue(String topic, String value);
};

#endif
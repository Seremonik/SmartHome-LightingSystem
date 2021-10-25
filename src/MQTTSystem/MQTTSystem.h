#ifndef MQTTSystem_H
#define MQTTSystem_H

#include "MQTTSystem.h"
#include <Arduino.h>
#include <Ethernet.h>
#include <PubSubClient.h>

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
    unsigned long initializationTime = 0;

    EthernetClient *ethClient;
    PubSubClient *mqttClient;
    static void SubscribeReceive(char *topic, byte *payload, unsigned int length);
    void InitializeMQTT();
    bool TimePast(unsigned long previousTime, unsigned long interval);

public:
    MQTTSystem();
    ~MQTTSystem();
    void InitializeEthernet();
    void Update();
};

#endif
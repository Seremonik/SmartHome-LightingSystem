
#include "MQTTSystem.h"

byte mac[] = {0xDE, 0x3D, 0x0E, 0xEF, 0xFE, 0xED};
const char *server = "test.mosquitto.org";
const int port = 1883;
const char *clientID = "Light_System_1";
const char *username = "";
const char *password = "";

MQTTSystem::MQTTSystem()
{
}

MQTTSystem::~MQTTSystem()
{
}

void MQTTSystem::SubscribeReceive(char *topic, byte *payload, unsigned int length)
{
}

void MQTTSystem::InitializeEthernet()
{
    Serial.println("Initializing Ethernet...");
    ethClient = new EthernetClient;
    mqttClient = new PubSubClient(*ethClient);

    Ethernet.begin(mac);
    initializationTime = millis();
    Serial.println("Finished Initializing Ethernet.");
}

void MQTTSystem::InitializeMQTT()
{
    Serial.println("Initializing MQTT...");

    mqttClient->setServer(server, port);

    if (mqttClient->connect(clientID, username, password))
    {
        mqttClient->publish("lightController/living_room/0", "1");
        Serial.println("Connection has been established, well done");

        isMqttInitialized = true;
        mqttClient->setCallback(SubscribeReceive);
        isMqttInitialized = true;
        return;
    }

    Serial.println("Looks like the server connection failed...");
    initializationTime = millis();
}

void MQTTSystem::Update()
{
    if (!isMqttInitialized && TimePast(initializationTime, 3000))
    {
        InitializeMQTT();
    }
}

bool MQTTSystem::TimePast(unsigned long previousTime, unsigned long interval)
{
    return ((unsigned long)(millis() - previousTime)) >= interval;
}

#include "MQTTSystem.h"

byte mac[] = {0xDE, 0x4A, 0x0E, 0xAC, 0xFE, 0xED};
const char *server = "192.168.0.241";
const int port = 1883;
const char *clientID = "Lighting System 1";
const char *username = "MQTT_User";
const char *password = "mqtt";

MQTTSystem::MQTTSystem()
{
}

MQTTSystem::~MQTTSystem()
{
}

void MQTTSystem::SetValue(String topic, String value)
{
    if (isMqttInitialized)
    {
        mqttClient.publish(topic, value, true, 1);
    }
}

void MQTTSystem::InitializeEthernet()
{
    initializationTime = millis();
    Serial.println("Initializing Ethernet...");
    if (Ethernet.linkStatus() == 1)
    {
        if (Ethernet.begin(mac) == 0)
        {
            Serial.println("Ethernet initialization failed. DHCP failure");
            return;
        }
        Serial.println("Finished Initializing Ethernet.");
        InitializeMQTT();
        isEthernetInitialized = true;
        return;
    }
    Serial.println("Ethernet initialization failed. no connection");
}

void MQTTSystem::InitializeMQTT()
{
    Serial.println("Initializing MQTT...");

    mqttClient.begin(server, ethClient);
    mqttClient.setWill("LightSystem/Connected", "0", true, 1);

    if (mqttClient.connect(clientID, username, password))
    {
        isMqttInitialized = true;
        mqttClient.subscribe("LightSystem/#");
        mqttClient.publish("LightSystem/Connected", "1", true, 1);

        Serial.println("Connection has been established, well done");
        return;
    }

    Serial.println("Looks like the server connection failed...");
    initializationTime = millis();
}

void MQTTSystem::Update()
{
    if (isMqttInitialized)
    {
        mqttClient.loop();
    }
    if (TimePast(initializationTime, 3000))
    {
        if (isMqttInitialized && !mqttClient.connected())
        {
            isMqttInitialized = false;
            isEthernetInitialized = false;
        }
        if (!isEthernetInitialized)
        {
            InitializeEthernet();
        }
        else if (!isMqttInitialized)
        {
            InitializeMQTT();
        }
    }
}
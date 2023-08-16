
#include "MQTTSystem.h"

#ifdef Lights 
    byte Mac[] = {0xDE, 0x4A, 0x0E, 0xAC, 0xFE, 0xED};
    const char *clientID = "Lighting System2";
#endif
#ifdef Shutters
    byte Mac[] = {0xAA, 0x4A, 0x0E, 0xCC, 0xCC, 0xED};
    const char *clientID = "Shutters System";
#endif

const char *server = "100.168.1.60";
const int port = 1883;
const char *username = "mqttclient";
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
    if (Ethernet.linkStatus() == LinkON)
    {
        if (Ethernet.begin(Mac) == 0)
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
    mqttClient.setWill("LightSystem/Availablity", "offline", true, 1);

    if (mqttClient.connect(clientID, username, password))
    {
        isMqttInitialized = true;
        mqttClient.subscribe("LightSystem/#");
        mqttClient.publish("LightSystem/Availablity", "online", true, 1);

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
        isEthernetInitialized = Ethernet.linkStatus() == LinkON;

        if (isMqttInitialized && !mqttClient.connected())
        {
            Serial.println(mqttClient.lastError());
            isMqttInitialized = false;
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
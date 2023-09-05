
#include "MQTTSystem.h"

#ifdef Lights 
    byte Mac[] = {0xDE, 0x4A, 0x0E, 0xAC, 0xFE, 0xED};
    const char *clientID = "Lighting System";
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
        Serial.print("Local IP:");
        Serial.println(Ethernet.localIP());
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
    mqttClient.setWill((systemTopic + "Availablity").c_str(), "offline", true, 1);

    if (mqttClient.connect(clientID, username, password))
    {
        isMqttInitialized = true;
        mqttClient.subscribe((systemTopic + "#").c_str());
        mqttClient.publish((systemTopic + "Availablity").c_str(), "online", true, 1);

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
        isEthernetInitialized = isEthernetInitialized && Ethernet.linkStatus() == LinkON;

        if (!isEthernetInitialized)
        {
            InitializeEthernet();
        }
        else if (isMqttInitialized && !mqttClient.connected())
        {
            Serial.println(mqttClient.lastError());
            isMqttInitialized = false;
        }
        else if (!isMqttInitialized)
        {
            InitializeMQTT();
        }
    }
}
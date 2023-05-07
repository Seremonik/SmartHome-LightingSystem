#include "MomentarySwitch.h"

MomentarySwitch::MomentarySwitch(int *buttonPins,
                         int buttonsCount,
                         int *outputPin,
                         int outputCount,
                         String mqttTopic) : Switch(buttonPins, buttonsCount, outputPin, outputCount)
{
    
}

MomentarySwitch::~MomentarySwitch()
{
}

void MomentarySwitch::Update()
{
    for (int i = 0; i < buttonsCount; i++)
    {
        buttons[i].Update();
        if (buttons[i].HasChangedSate(buttonIsPressed))
        {
            for (int i = 0; i < outputCount; i++)
            {
                digitalWrite(outputPins[i], !buttonIsPressed);
            }
        }
    }
}
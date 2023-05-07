#ifndef MomentarySwitch_H
#define MomentarySwitch_H

#include "../Switch/Switch.h"

class MomentarySwitch : public Switch
{
    private:
    bool buttonIsPressed;

    public:
    MomentarySwitch(int *buttonPins, int buttonsCount, int *outputPin, int outputCount, String mqttTopic);
    ~MomentarySwitch();
    void Update();
};

#endif
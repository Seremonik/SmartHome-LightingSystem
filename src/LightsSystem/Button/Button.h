#ifndef Button_H
#define Button_H

#include "Arduino.h"
#include "../../Utils/Util.h"

class Button
{

private:
    int pin;
    bool currentState = false;
    unsigned long millisInCurrentState;
    bool hasValueChanged = false;

public:
    bool IsPressed = false;
    Button();
    void Initialize(int pin);
    void Update();
    bool HasChangedSate(bool &isPressed);
};

#endif
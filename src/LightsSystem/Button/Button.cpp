#include "Button.h"

Button::Button()
{
}

void Button::Initialize(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    IsPressed = false;
    millisInCurrentState = 0;
}

void Button::Update()
{
    currentState = !digitalRead(pin);

    if (currentState != IsPressed)
    {
        if (TimePast(millisInCurrentState, 50))
        {
            IsPressed = currentState;
            hasValueChanged = true;
            millisInCurrentState = millis();
        }
    }
    else
    {
        millisInCurrentState = millis();
    }
}

bool Button::HasChangedSate(bool &isPressed)
{
    isPressed = this->IsPressed;
    if (hasValueChanged)
    {
        hasValueChanged = false;
        return true;
    }

    return false;
}
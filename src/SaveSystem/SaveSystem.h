#ifndef SaveSystem_H
#define SaveSystem_H

#include <SPI.h>
#include <SD.h>

class SaveSystem
{
private:
    bool isInitialized = false;

public:
    SaveSystem();
    ~SaveSystem();
    void Initialize();
    void SavePinState(int pin, bool isOn);
    bool isPinOn(int pin);
};

#endif

#include "Util.h"

bool TimePast(unsigned long previousTime, unsigned long interval)
{
    return ((unsigned long)(millis() - previousTime)) >= interval;
}
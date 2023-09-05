#ifndef UTILS_H
#define UTILS_H

//#define Lights
#define Shutters

#include <Arduino.h>

#ifdef Lights
static String systemTopic = "LightSystem/";
#endif
#ifdef Shutters
static String systemTopic = "ShutterSystem/";
#endif

bool TimePast(unsigned long previousTime, unsigned long interval);

#endif
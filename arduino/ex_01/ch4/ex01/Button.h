#pragma once
#include <Arduino.h>

class Button{
    int pin;
    bool state_current;
    bool state_previous;
    void (*callback)();
    public:
    Button(int pin);
    int read();
    void check();
    void setCallback(void (*callback)());

};
#include "Led.h"
#include "Button.h"


Led led1(4);

Button btn1(9);

bool blinkPlay = false;
int blinkTimer= -1;
void led1OnOff(){
    led1.toggle();
}

void setup(){
    Serial.begin(9600);
}

void loop(){
    led1.set(btn1.read());
}
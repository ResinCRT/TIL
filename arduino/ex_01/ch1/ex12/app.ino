#include "SimpleTimer.h"

SimpleTimer timer;

int pin_LED1=13;
int pin_LED2=12;
int pin_LED3=9;
boolean state=false;

void blink_1000(){
    int state = digitalRead(pin_LED1);
    digitalWrite(pin_LED1,!state);
}
void blink_500(){
    int state = digitalRead(pin_LED2);
    digitalWrite(pin_LED2,!state);
}
void blink_200(){
    int state = digitalRead(pin_LED3);
    digitalWrite(pin_LED3,!state);
}
void PrintTest(){
    Serial.println("simple called");
}

void setup(){
    Serial.begin(9600);
    pinMode(pin_LED1,OUTPUT);
    pinMode(pin_LED2,OUTPUT);
    pinMode(pin_LED3,OUTPUT);
    timer.setInterval(1000,blink_1000);
    timer.setInterval(500,blink_500);
    timer.setInterval(200,blink_200);
}
void loop(){
    timer.run();
}
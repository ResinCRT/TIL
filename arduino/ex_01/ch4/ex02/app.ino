#include "SimpleTimer.h"
#include "Led.h"
#include "Button.h"


SimpleTimer timer;

Led led1(4);
Led led2(6);
Led led3(7);

Button btn1(12);
Button btn2(10);
Button btn3(11);

bool blinkPlay = false;
int blinkTimer= -1;

void led2OnOff(){
    led2.toggle();
}
void led1OnOff(){
    led1.toggle();
}
void led3Blink(){
    led3.toggle();
}

void led3BlinkControl(){
    blinkPlay = !blinkPlay;
    if(!blinkPlay){
        led3.off();
    }
    timer.toggle(blinkTimer);

}
void setup(){
    Serial.begin(9600);
    btn2.setCallback(led1OnOff);
    btn2.setCallback(led2OnOff);
}

void loop(){
    timer.run();
    btn1.check();
    btn2.check();
}
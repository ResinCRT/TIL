#include "SimpleTimer.h"
#include "Led.h"
#include "Button.h"


SimpleTimer timer;

Led led1(4);
Led led2(6);
Led led3(7);

Button btn1(9);
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
    btn2.setCallback(led2OnOff);
    btn3.setCallback(led3BlinkControl);
    blinkTimer = timer.setInterval(500, led3Blink);
    timer.disable(blinkTimer);
}

void loop(){
    timer.run();
    led1.set(btn1.read());
    btn2.check();
    btn3.check();
}
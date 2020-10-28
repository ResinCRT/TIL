#include <Minicom.h>
#include <Servo.h>
#include "Joystick.h"

Servo servo;
Joystick joy(A0, A1, 3);
Minicom com;
const int SERVO_PIN = 4;
bool mode;

void readJoystick(){
    joystick_value_t value = joy.read();
    if(mode){
        com.print(0,"X", "Y" ,value.x, value.y); //Minicom.h 에 함수 추가
    }
    else{
        servo.write(value.x);
        com.print(1, "Angle",value.x);
    }
}
void changeMode(){
    mode = !mode;
    if(mode){
        joy.setRangeX(-255,255);
    }
    else{
        joy.setRangeX(0,180);
    }
}

void setup(){
    com.init();
    servo.attach(SERVO_PIN);
    joy.setRangeX(-255,255);
    joy.setRangeY(-255,255);
    joy.setCallback(changeMode);
    mode = true;
    com.setInterval(50, readJoystick);
}

void loop(){
    com.run();
    joy.check();
}
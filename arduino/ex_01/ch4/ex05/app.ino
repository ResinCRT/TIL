#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SimpleTimer.h>
#include "Joystick.h"
#include <led.h>

Servo servo;
Joystick joy(A0, A1, 3);
LiquidCrystal_I2C lcd(0x27,16,2);
SimpleTimer timer;
Led led(8);
const int SERVO_PIN = 4;
bool mode;

void readJoystick(){
    joystick_value_t value = joy.read();
    char buff[17];
    if(mode){
        sprintf(buff, "x:%4d/y:%4d",value.x, value.y);
        lcd.setCursor(0,0);
        lcd.print(buff);
    }
    else{
        servo.write(value.x);
        sprintf(buff, "Angle: %3d",value.x);
        lcd.setCursor(0,1);
        lcd.print(buff);
    }
}
void checkLed(){
    if(mode){
        led.off();
    }
    else{
        led.on();
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
    lcd.init();
    lcd.backlight();
    lcd.clear();
    servo.attach(SERVO_PIN);
    joy.setRangeX(-255,255);
    joy.setRangeY(-255,255);
    joy.setCallback(changeMode);
    mode = true;
    timer.setInterval(50, readJoystick);
}

void loop(){
    timer.run();
    joy.check();
    checkLed();
}
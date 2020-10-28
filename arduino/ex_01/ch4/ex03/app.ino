#include <SimpleTimer.h>
#include <Button.h>
#include <Led.h>
#include <LiquidCrystal_I2C.h>


SimpleTimer timer;
LiquidCrystal_I2C lcd(0x27,16,2);

Led led1(4);
Led led2(6);
Led led3(7);

Button btn1(9);
Button btn2(10);
Button btn3(11);

int timerId = -1;

int blinkTimerId = -1;

int state = 0;
unsigned long startTime = 0;
unsigned long stopTime = 0;
void printTime(unsigned long t, int row){
    char buff[17];


    int misec = t % 1000 / 100;
    t = t/1000;
    int h = t/3600;
    int m = (t - (h * 3600)) / 60;
    int s = t - (h * 3600 + m * 60);
    sprintf(buff, "%02d:%02d:%02d.%d",h,m, s,misec);

    lcd.setCursor(0, row);
    lcd.print(buff);

}
void printTime(){
    unsigned long t = millis();
    unsigned long diff = t - startTime;
    printTime(diff, 0);
}
    
void startStop(){
    if(state == false){
        startTime = millis();
        timer.enable(blinkTimerId);
        led2.off();
        state = true;
    }
     timer.toggle(timerId);

}
void blink(){
    led3.toggle();
}
void reset(){
    state = false;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("00:00:00.0");
    led2.on();
    led3.off(); 
    timer.disable(timerId);
    timer.disable(blinkTimerId);
}
void laptime(){
    if(state){
        unsigned long t = millis();
        unsigned long diff = t - startTime;
        printTime(diff, 1);
    }
}
void setup(){
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

    timerId = timer.setInterval(100, printTime);
    blinkTimerId = timer.setInterval(250,blink );
    reset();

    btn1.setCallback(startStop);
    btn2.setCallback(laptime);
    btn3.setCallback(reset);

}
void loop(){
    timer.run();
    btn1.check();
    btn2.check();
    btn3.check();
}

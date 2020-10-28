#include <Led.h>
#include <AnalogSensor.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleTimer.h>

AnalogSensor light(A0,0, 100);
Led led1(3);
LiquidCrystal_I2C lcd(0x27, 16,2);
void lcdPrint(){
    char buff[17];
    sprintf(buff, "Read Value = %3d", light.read());
    lcd.setCursor(0,0);
    lcd.print(buff);
}
void checkLight(){
    int num = light.read();
    if(num > 80){
        led1.on();
    }
    else{
        led1.off();
    }
}
void setup(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void loop(){
    lcdPrint();
    checkLight();
    delay(200);
}
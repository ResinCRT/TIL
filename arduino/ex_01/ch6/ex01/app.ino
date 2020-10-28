#include "Wifiutil.h"

const char SSID[] = "hwsally";
const char PASSWORD[] = "hwsally2721";

Wifiutil wifi(2,3);

void setup(){

    Serial.begin(9600);
    wifi.init(SSID, PASSWORD);
}

void loop(){
    if(wifi.check()){
        ;
    }
}
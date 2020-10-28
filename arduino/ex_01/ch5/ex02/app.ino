#include <Minicom.h>
#include "Ultra.h"

#include <Led.h>
#include "Pulse.h"
Minicom com;
Pulse pulse(100,500);
Ultra ultra(2,3);

Led led(8);


void checkDistance(){
    int distance = ultra.read();
    com.print(0, "distance", distance);
    if(distance<10){
        led.on();
        int offDelay = map(distance, 0, 9, 100, 1000);
        pulse.setDelay(10,offDelay);
        if(!pulse.getState()){
            pulse.play();
        }
    }
    else{
        led.off();
        if(pulse.getState()){
            pulse.stop();
        }
    }

}
void setup(){
    com.init();
    com.setInterval(1000,checkDistance);
}

void loop(){
    com.run();
}

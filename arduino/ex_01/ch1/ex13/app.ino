#include "SimpleTimer.h"

SimpleTimer timer;
int RGBpin[] = {9,10,11};
boolean state=false;



void setup(){
    Serial.begin(9600);
    randomSeed(analogRead(A0));
    for(int i=0;i<3;i++){
        analogWrite(RGBpin[i],255);
        for(int j=0; j<3; j++){
            if(i!=j){
                analogWrite(RGBpin[j],0);
            }
        }
        delay(1000);
    }
}
void loop(){
    for(int i=0;i<3;i++){
        analogWrite(RGBpin[i],random(256)); 
    }
    delay(1000);
}
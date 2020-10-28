int pin_LED=13;
int pin_LED2=8;
boolean state1 = false;
boolean state2 = false;
unsigned long time_previous, time_current;
unsigned long time_previous2, time_current2;
unsigned long count = 0;
void blink_1000(){
    time_current=millis();\
    if(time_current - time_previous>=1000){
        time_previous=time_current;
        state1=!state1;
        digitalWrite(pin_LED,state1 );
    }
}
void blink_500(){
    time_current2=millis();
    if(time_current2 - time_previous2>=500){
        time_previous2=time_current2;
        state2=!state2;
        digitalWrite(pin_LED2,state2 );
    }
}
void setup(){
    Serial.begin(9600);
    pinMode(pin_LED,OUTPUT);
    pinMode(pin_LED2,OUTPUT);
    digitalWrite(pin_LED,LOW);
    digitalWrite(pin_LED2,LOW);
    time_previous=millis();
    time_previous2=millis();
}

void loop(){
    blink_1000();
    blink_500();
}
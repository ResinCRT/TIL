int pin_LED = 13;
    
void setup(){
    Serial.begin(9600);
    pinMode(pin_LED,OUTPUT);
}

void loop(){
    if(Serial.available()){
        char inChar = Serial.read();
        if(inChar =='\r'||inChar == '\n') return;
        if(inChar == '1'){
            digitalWrite(pin_LED,HIGH);
        }
        else if(inChar == '2'){
            digitalWrite(pin_LED, LOW);
        }
        else{
            digitalWrite(pin_LED, LOW);
        }
    }
}
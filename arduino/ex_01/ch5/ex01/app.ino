int pSensor = A0;
int ledpin = 3;

void setup(){
    Serial.begin(9600);
    pinMode(ledpin, OUTPUT);
}

void loop(){
    int readVal = analogRead(pSensor);
    Serial.print("Read Value = ");
    Serial.println(readVal);

    if(readVal<200){
        digitalWrite(ledpin, HIGH);

    }
    else{
        digitalWrite(ledpin,LOW);

    }
    delay(200);
}
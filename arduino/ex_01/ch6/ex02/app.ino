#include "Wifiutil.h"

const char SSID[] = "hwsally";
const char PASSWORD[] = "hwsally2721";
const char server[] = "arduino.cc";
Wifiutil wifi(2,3);
WiFiEspClient client;
void request(){
    if (client.connect(server, 80)){
        Serial.println("Connected to server");// Make a HTTP request
        client.println("GET /asciilogo.txt HTTP/1.1");
        client.println("Host: arduino.cc");
        client.println("Connection: close");
        client.println();
    }
}
void response(){
    while(client.available()){
        char c = client.read();
        Serial.write(c);
    }
}
void setup(){

    Serial.begin(9600);
    wifi.init(SSID, PASSWORD);
    request();
}

void loop(){
    response();
}
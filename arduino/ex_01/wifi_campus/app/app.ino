#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "Wifiutil.h"

SoftwareSerial softSerial(2,3);
const char ssid[] = "Campus7_Room3_2.4";
const char password[] = "12345678";
const char mqtt_server[] = "192.168.0.109";

WiFiEspClient espClient;
PubSubClient client(espClient);
Wifiutil util(2,3);
int messagecount;
int recieved;


void reconnect(){
    while(!client.connected()){
        Serial.print("Attempting MQTT connection...");

        if(client.connect("ESP8266Client")){
            Serial.println("connected");
            client.subscribe("IoT3/home/living/LED/info");
        }
        else{
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds.");
            delay(5000);
        }
    }
}
void publish(){
    char message[10];
    sprintf(message, "%d:test", messagecount);
    messagecount++;
    client.publish("IoT3/home/living/LED", message);
}
void receive_message(){
    char message[10];
    sprintf(message, "receiv %d",recieved);
    recieved++;
    client.publish("IoT3/home/server", message);
}
void callback(char* topic, byte* payload, unsigned int length){
    receive_message();
}
void mqtt_init(){
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}
Ticker publishTicker(publish, 2000);

void setup(){
    util.init(ssid,password);
    messagecount=0;
    mqtt_init();
    Serial.begin(9600);
    publishTicker.start();
}

void loop(){
    if(!client.connected()){
        reconnect();
    }
    client.loop();
    publishTicker.update();
}

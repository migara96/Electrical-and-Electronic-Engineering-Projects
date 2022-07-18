#include <ESP8266WiFi.h> //thingspeak
#include "ThingSpeak.h"
const char* ssid="Migara";
const char* password="Migara@12345";
unsigned long myChannelNumber =1001400;
const char* myWriteAPIkey="6Q72P02Q5GEMHBF0";// thingspeak
const char* myReadAPIkey="EMNYDVST5A5I70FU"; //thingspeak
unsigned long myChannelNumber1 =1091314;
const char* myWriteAPIkey1="WLJOQ05IKWD5OYQN";// thingspeak
const char* myReadAPIkey1="JDGBVK55N9MRYTGG"; //thingspeak
////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D7);
///////////////////////////////////////////////////////////////////
WiFiClient client;
/////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;
float lux;
float prs;
float alt;
float hum;
float tem;
float airqual;
float degreeValue;
float rpm;
void setup() {
Wire.begin(); //i2c
Serial.begin(115200);
s.begin(115200);
WiFi.begin(ssid,password);
while(!Serial) continue;
while( WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.println("connecting......");
}
Serial.println("WiFi is connected");
ThingSpeak.begin(client); //thingspeak
}
void loop() {
if (Serial.available()){
prs =Serial.read();
Serial.print("prs:");
Serial.println(prs*10);
}
if (Serial.available()){
Serial.print("alt:");
alt =Serial.read();
Serial.println(alt*10);
}
if (Serial.available()){
hum =Serial.read();
Serial.print("hum:");
Serial.println(hum*10);
}
if (Serial.available()){
Serial.print("tem:");
tem =Serial.read();
Serial.println(tem*10);
}
if (Serial.available()){
airqual =Serial.read();
Serial.print("airqual:");
Serial.println(airqual*10);
}
if (Serial.available()){
degreeValue =Serial.read();
Serial.print("degreeValue:");
Serial.println(degreeValue*10);
}
if (Serial.available()){
rpm =Serial.read();
Serial.print("rpm:");
Serial.println(rpm*10);
}
lightIntensity();
tothingspeak();
}
void tothingspeak(){
ThingSpeak.setField(1,prs);
ThingSpeak.setField(2,alt);
ThingSpeak.setField(3,hum);
ThingSpeak.setField(4,tem);
ThingSpeak.setField(5,airqual);
ThingSpeak.setField(6,degreeValue);
ThingSpeak.setField(7,rpm);
ThingSpeak.setField(8,lux);
ThingSpeak.writeFields(myChannelNumber,myWriteAPIkey);
}
///////////////////////////////////////////////////////////
void lightIntensity(){
lightMeter.begin();
lux = lightMeter.readLightLevel(true);
Serial.print("Light: ");
Serial.print(lux);
Serial.println(" lx");
delay(2000);
}

#include <dht.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal.h>

BH1750 lightMeter;
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

//const byte rxPin = 9;
//const byte txPin = 10;

//SoftwareSerial mySerial  (rxPin, txPin);

int windDir = A0;
int dht_pin = A1;
int air_gas = A2;
float revolutions;
int timeold;
int timedifference;
int rpm;

dht DHT;

void setup() 
{
  pinMode(windDir, INPUT);
  pinMode(dht_pin, INPUT);
  pinMode(air_gas, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, rpm_fun, RISING);
  revolutions = 0;
  timeold = 0; 
  lcd.begin(16, 2);
  
  //mySerial.begin(9600);
  //sendMessage();
}

void loop() {
  Serial.println();
  Serial.println("Weather Details: ");
  Serial.print("Wind Direction: ");
  lcd.clear();
  windDirection();
  lcd.clear();
  tempHumd();
  lcd.clear();
  air_qual();
  lcd.clear();
  windspeed();
  lcd.clear();
  lightIntensity();
  delay(500);
}

void rpm_fun()
{
  revolutions++;
}

void air_qual(){
  int air_qual = analogRead(air_gas);
  Serial.print("Air Quality = ");
  lcd.print("Air Quality = ");
  Serial.print(air_qual, DEC);  
  lcd.print(air_qual, DEC);            
  Serial.println(" PPM");          
  lcd.println(" PPM");
  
}

void tempHumd(){
    DHT.read11(dht_pin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.println("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    lcd.print("Current humidity = ");
    lcd.print(DHT.humidity);
    lcd.println("%  ");
    lcd.print("temperature = ");
    lcd.print(DHT.temperature); 
    lcd.println("C  ");  
}
/*
void windspeed(){
  if(revolutions>=1){
    timedifference = (millis()-timeold);
    timeold = millis();
    rpm = (revolutions/timedifference)*60000;
    revolutions = 0;

    Serial.print("Total time:");
    Serial.print(timeold);
    Serial.print("Time Difference: ");
    Serial.print(timedifference);
    Serial.print("rpm: ");
    Serial.println(rpm);
  }
}
*/
void lightIntensity(){
  Wire.begin();
  lightMeter.begin();
  float lux = lightMeter.readLightLevel(true);
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  lcd.print("Light: ");
  lcd.print(lux);
  lcd.println(" lx");
  delay(2000);
}
/*
void sendMessage(){
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+94770471553\"\r");
  delay(1000);
  mySerial.println("Weather Details");
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
}
*/

int windDirection()
{
  int inputValue = analogRead(windDir);
  int degreeValue = map(inputValue, 0, 1023, 0, 360);
  //Serial.println(degreeValue);
  
  if (degreeValue == 0||degreeValue == 1) {
    Serial.println("North");
    Serial.println("North");
  }
  else if (degreeValue > 1 && degreeValue < 45) {
    Serial.print(degreeValue);
    Serial.println(" degreees to east from north");
  }
  else if (degreeValue == 45) {
  Serial.println("North-East");
  }
  else if (degreeValue > 45 && degreeValue < 90) {
    Serial.print(degreeValue);
    Serial.println(" degrees to east from north");
  }
  else if (degreeValue == 90) {
    Serial.println("East");
  }
  else if (degreeValue > 90 && degreeValue < 135) {
    Serial.print(degreeValue-90);
    Serial.println(" degrees to South from east");
  }
  else if (degreeValue == 135) {
    Serial.println("South-East");
  } 
  else if (degreeValue > 135 && degreeValue < 180) {
    Serial.print(degreeValue-90);
    Serial.println(" degrees to south from east");
  }
  else if (degreeValue == 180) {
    Serial.println("South");
  }
  else if (degreeValue > 180 && degreeValue < 225) {
    Serial.print(degreeValue-180);
    Serial.println(" degrees to west from south");
  }
  else if (degreeValue == 225) {
    Serial.println("South-west");
  }
  else if (degreeValue > 225 && degreeValue < 270) {
    Serial.print(degreeValue-180);
    Serial.println(" degrees to west from south");
  }
  else if (degreeValue == 270) {
    Serial.println("West");
  }
  else if (degreeValue > 270 && degreeValue < 315) {
    Serial.print(degreeValue-270);
    Serial.println(" degrees to north from west");
  }
  else if (degreeValue == 315) {
    Serial.println("north-westh");
  }
  else if (degreeValue > 315 && degreeValue < 360) {
    Serial.print(degreeValue-270);
    Serial.println(" degrees to north from west");
  } 
 else {
  Serial.println("Invalid result");
 }

 
}

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

const int numofBytes = 11;
const int numofutBytes = 5;
const int temperature_bytes = 7;
const int distance_bytes = 5;
char sensorValue[numofBytes];
char utValue [numofutBytes];
char temperature[temperature_bytes] ; 
char distance[distance_bytes] ;

LiquidCrystal lcd(7,4 , 5 , 10 , 11 , 12);
AltSoftSerial blueSerial;

void RecieveSensorData(char sensorValue[numofBytes]){
  int i = 0 ;
   // should be uncomment
  while(Serial.available() && i < numofBytes - 1){
    sensorValue[i] = Serial.read();
    if(sensorValue[i] == '#')
      {
        i++;
        sensorValue[i++]='\0';
        break;
      }
    i++;
  }
}
void RecieveUTData(char utValue [numofutBytes]){
  
  int i = 0;

  while(blueSerial.available() && i < numofutBytes - 1){
    
    utValue[i] = blueSerial.read();
    // if (temp2[])
    i++;
  }
  utValue[i++]='\0';
}
void ShowOnLCD(char utValue [numofutBytes],char temperature[temperature_bytes],char distance[distance_bytes]){

  lcd.setCursor(0,0);
  lcd.print("UT value: ");
  lcd.println(utValue);
 
  lcd.setCursor(0, 1);
  
  lcd.print("Temp: ");
  lcd.println(temperature);
  
  lcd.setCursor(-4,2);
  
  lcd.print("Dist: ");
  lcd.println(distance);
  
}
void Splitter(char* temperature , char* distance , char* temp){
  int pos = 0;
  String token;
  while(sensorValue[pos] != '$'){
    temperature[pos] = sensorValue[pos];
    pos++;
  }
  temperature[pos] = '\0';
  pos++;
  int j = 0;
  while(sensorValue[pos] != '#'){
    distance[j++] = sensorValue[pos];
    pos++;
  }
  distance[pos] = '\0';
  
}

 void setup() {

    blueSerial.begin(9600);
    Serial.begin(9600);
    lcd.begin(4, 20);
 }

 void loop() {
  
  
  RecieveSensorData(sensorValue);
  
  Splitter(temperature , distance , sensorValue); 
  
  RecieveUTData(utValue);

  ShowOnLCD(utValue,temperature,distance);
    
  delay(100);
  
 }
#include <Arduino.h>
#include <Wire.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

const int numofBytes = 11;
const int temperature_bytes = 7;
const int distance_bytes = 5;

char temp[numofBytes];

char temperature[temperature_bytes] ; 
char distance[distance_bytes] ;

//LiquidCrystal lcd(7,8 , 9 , 10 , 11 , 12);
LiquidCrystal lcd(7,4 , 5 , 10 , 11 , 12);
AltSoftSerial altSerial;
void splitter(char* temperature , char* distance , char* temp){
  int pos = 0;
  String token;
  while(temp[pos] != '$'){
    temperature[pos] = temp[pos];
    pos++;
  }
  temperature[pos] = '\0';
  pos++;
  int j = 0;
  while(temp[pos] != '#'){
    distance[j++] = temp[pos];
    pos++;
  }
  distance[pos] = '\0';
  
}

 void setup() {

    Serial.begin(9600);
    altSerial.begin(9600);
    //altSerial.println("hello world!");
    lcd.begin(4, 20);
 }

 void loop() {
  int i = 0 ;
   
  while(Serial.available() && i < numofBytes - 1){
    temp[i] = Serial.read();
    if(temp[i] == '#')
      {
        i++;
        temp[i++]='\0';
        break;
      }
    i++;
  }
  
  altSerial.println(temp);
  splitter(temperature , distance , temp);  
  lcd.print("Temp: ");
  lcd.print(temperature);
  
  lcd.setCursor(0, 1);
  
  lcd.print("Dist: ");
  lcd.print(distance);
  
  lcd.setCursor(0, 0);
  delay(200);
  
 

 }
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>


char temp[9];
LiquidCrystal lcd(7,8 , 9 , 10 , 11 , 12);
  
 void setup() {

    Serial.begin(9600);
    lcd.begin(4, 20);
 }

 void loop() {
  int i = 0 ;
 if (Serial.available()) {
  
  while(Serial.available() && i<4){
    temp[i++] = Serial.read();
  }
  temp[i++]='\0';
  
  lcd.write(temp);
  delay(200);
  lcd.setCursor(0, 0);
  }

 }
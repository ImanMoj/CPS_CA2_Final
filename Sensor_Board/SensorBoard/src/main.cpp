#include <Arduino.h>
#include <Wire.h>
// #include <String.h>
#include <LM35.h>

LM35 temp_sensor(A1);
int value;

void sendTemperature(){
  
  value=temp_sensor.cel();
  char b [4];
  itoa(value, b, 10);
  Serial.write(b , 8);
  delay(400);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sendTemperature();
}


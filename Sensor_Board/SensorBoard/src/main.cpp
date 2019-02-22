#include <Arduino.h>
#include <Wire.h>
#include <String.h>
#include <LM35.h>
#include <HCSR04.h>


float temperature;
const int trigPin = 12;
const int echoPin = 13;
const int numofBytes = 11;
long duration;
int distance;
String message;
String str_temperature ;
String str_distance ;
LM35 temp_sensor(A1);
HCSR04 hcsr04(trigPin, echoPin, 20, 4000);

String concatinate(float temperature , int distance){
   
   str_temperature = String(temperature);
   str_distance = String(distance);
   str_temperature += "$";
   str_temperature += str_distance;
   str_temperature += "#";
   return str_temperature ;
   
 }


void send(String str){
  char chararray [numofBytes];
  str.toCharArray(chararray , numofBytes);
  Serial.write(chararray);
  // Serial.write('\n');
}





void setup()
{
  Serial.begin(9600);
}

void loop()
{
  temperature = temp_sensor.cel();
  distance = hcsr04.distanceInMillimeters();
  message = concatinate(temperature , distance);
  send(message);
  // Serial.println(message);
  delay(200);
}


#include <Arduino.h>
#include <Wire.h>
#include <AltSoftSerial.h>

const int UT_SENSOR_ADDRESS = 110;
const int X_FIRST_REG = 10;
const int Y_FIRST_REG = 40;
const int numofBytes = 5;
float value = 0;
float x ;
float y ;
AltSoftSerial blueSerial;


void turnSensorOn(){
  
  Wire.begin(UT_SENSOR_ADDRESS);
  Wire.beginTransmission(UT_SENSOR_ADDRESS);
  Wire.write(0);
  Wire.write(1);
  Wire.endTransmission();
}

union {
    char c[4];
    float f;
  } chartof;


float read_data(const int first_reg_adr ){
  
  for(int i = 0;i<4;i++){
    Wire.beginTransmission(UT_SENSOR_ADDRESS);
    Wire.write(first_reg_adr + i);
    Wire.endTransmission(); 
    Wire.requestFrom(UT_SENSOR_ADDRESS,1);
  
    while(Wire.available())    // slave may send less than requested
    { 
      chartof.c[i] = Wire.read();    // receive a byte as character
    }

  }
  return chartof.f;
}
void send(String str){
  char chararray [numofBytes];
  str.toCharArray(chararray , numofBytes);
  blueSerial.write(chararray);
}
void setup() {

  blueSerial.begin(9600);
  Serial.begin(9600);
  turnSensorOn();
  
}

void loop() {
  x = read_data(X_FIRST_REG); 
  y = read_data(Y_FIRST_REG);
  // Serial.println("X: ");
  // Serial.println(x);
  // Serial.println("Y: ");
  // Serial.println(y);
  value += x*x + y*y;
  // Serial.println("Value: ");
  // Serial.println(value);
  send(String(value));
  delay (100); 
  
}
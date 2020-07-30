#include <SoftwareSerial.h>
#include "HX711.h"
#include <stdlib.h>
SoftwareSerial nodemcu(7, 8); // nodemcu module connected here
#define DOUT  3
#define CLK  2
//HX711 scale(DOUT, CLK);
HX711 scale;
 
int rbutton = 6; // this button will be used to reset the scale to 0. 
String myString; 
String cmessage; // complete message
char buff[10];
float weight; 
float calibration_factor = 24621; // for me this vlaue works just perfect 419640 
void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  scale.begin (DOUT, CLK);
  pinMode(rbutton, INPUT_PULLUP); 
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
 
}
void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(5); //5
myString = dtostrf(weight, 3, 2, buff);
cmessage = cmessage + "Weight" + ":" + myString + "Kg"+","; 
 nodemcu.println(cmessage);
Serial.println(cmessage); 
cmessage = "";
 
  Serial.println();
 
  if ( digitalRead(rbutton) == LOW)
  {
     scale.set_scale();
  scale.tare(); //Reset the scale to 0
  }
 
  delay(500);
}

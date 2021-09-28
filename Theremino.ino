/*
  This projects is a theremin created with two ultrasonic sensors, one controls the frequency (tone) and the other controls the amplitude (volume).
  This project is a fork of two projects:
    - https://create.arduino.cc/projecthub/opus9/theremino-f72d32 (this project had library conflicts)
    - https://create.arduino.cc/projecthub/jvmccall/ultrasonic-theremin-033d6f (this project had typo errors in the code and a mistake in the schema)
  Resource on controlling similar potentiometer using SPI protocol, provides example code and electrical setup: http://www.learningaboutelectronics.com/Articles/MCP4131-digital-potentiometer-circuit.php
*/
                                                                                                                                                                                                                                                
//// NewTone is used to avoid the timer incompatibiliy of Tone with NewPing. Download https://bitbucket.org/teckel12/arduino-new-tone/downloads/ and import .zip
#include <NewTone.h>
#include <NewPing.h>
#define MIN_DISTANCE 60

int echo = 3;                            
int trigger = 4;
unsigned long TimeResponse;
float distance;
float tone1;

void setup() {                    // set all the pins 
  Serial.begin(9600); 
  pinMode(trigger, OUTPUT);       // tone sensor                    
  pinMode(echo, INPUT);           // tone sensor    

//                                // this has the speaker emit a start up sound from Low to High to Low
//  
//  for (int i = 50; i <= 400; i++)
//  {
//    pinMode(9, OUTPUT);
//    NewTone(9,i);
//    delay(10);
//  }
//  
//  delay(500);
//  
//  for (int i = 400; i >= 50; i--)
//  {
//    pinMode(9, OUTPUT);
//    NewTone(9,i);
//    delay(10);
//  } 
}

void loop() {  
  digitalWrite(trigger, HIGH);           
  delayMicroseconds(10);                  // creates a 10 microsecond pulse                      
  digitalWrite(trigger, LOW);                  
  TimeResponse = pulseIn(echo, HIGH);     // records how long it took to receive echo of the pulse
  distance = TimeResponse/58;
  delay(15);       
                                          // calculates distance in centimeters

  if (distance < MIN_DISTANCE) {          // conversion of distance into a value for a sound 
    tone1 = 50.0*pow(30,(distance/58));  // calculate frequency, range of about 50-360 Hz
    pinMode(9, OUTPUT);
    NewTone(9,tone1);
  } else {
    pinMode(9, OUTPUT); // this sets the sound to a high pitched noise when no distance is detected
    NewTone(9,0);
  } 
}

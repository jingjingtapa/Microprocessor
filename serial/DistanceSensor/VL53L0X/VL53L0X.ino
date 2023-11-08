#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int speakerPin = 8;
int forcepin = A1;
int tones[]={261,277,311}; // 연주할 톤의 진동수.
int input_data;

void setup() {
  Serial.begin(115200);
  pinMode(speakerPin,OUTPUT);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  // Serial.println("Adafruit VL53L0X ");
  // if (!lox.begin()) {
  //   Serial.println(F("Failed to boot VL53L0X"));
  //   while(1);
  // }
  // // power 
  // Serial.println(F("Start checking Distance...")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  int val = analogRead(forcepin);
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    //Serial.print("Distance (mm): "); 
    Serial.println(measure.RangeMilliMeter);
    Serial.println(analogRead(forcepin));
    
    // if (measure.RangeMilliMeter >= 150 & val <= 40 ) {
      
    //   // for(int i=0; i < sizeof(tones); i++)
    //   //   tone(speakerPin,tones[i]);
    //   //   delay(100);
    //   //   noTone(speakerPin);
    //   //   delay(500);
    // }

  }
    
  delay(100);

}

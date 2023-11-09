#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

////////////// 센서 핀 위치 설정 //////////////////

       /// INPUT 센서

int forcepin = A1;


       /// OUTPUT 장치

int BACKLIGHT = 8;  ///// 후미등 input
int speakerPin = 9; ///// 부저스피커 input
int tones[]={261,277,311}; // 연주할 톤의 진동수.
int delays = 30;
////////////// 졸음 판단 기준 변수들 /////////////////

int HEAD = 130;  
int GRIP = 100;
int EYE;

///////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  pinMode(speakerPin,OUTPUT);
  pinMode(BACKLIGHT,OUTPUT);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  // Serial.println("Adafruit VL53L0X ");
  if (!lox.begin()) {
     Serial.println(F("Failed to boot VL53L0X"));
     while(1);
   }
   // power 
  // Serial.println(F("Start checking Distance...")); 
}


void loop() {

  VL53L0X_RangingMeasurementData_t measure;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
  int force = analogRead(forcepin); // 압전센서의 측정값
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    
    if (measure.RangeMilliMeter >= HEAD & force <= GRIP ) {

      Serial.print("distance : "); Serial.print(measure.RangeMilliMeter); Serial.print(", force : "); Serial.print(force); Serial.println(" - WAKE UP");
      digitalWrite(BACKLIGHT,HIGH);
      delay(delays);
      digitalWrite(BACKLIGHT,LOW);
      delay(delays);
    ////////////// 부저 스피커 출력구문
    //  for(int i=0; i < sizeof(tones); i++)
    //    tone(speakerPin,tones[i]);
    //    delay(100);
    //    noTone(speakerPin);
    //    delay(500);
    }
    else{
      Serial.print("distance : "); Serial.print(measure.RangeMilliMeter); Serial.print(", force : "); Serial.println(force);
      delay(delays);
    }
  }
    
  delay(100);

}

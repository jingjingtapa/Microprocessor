#include "Adafruit_VL53L0X.h"
#include <DFRobot_ENS160.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define I2C_COMMUNICATION  //I2C communication. Comment out this line of code if you want to use SPI communication.
#ifdef  I2C_COMMUNICATION  //For Fermion version, the default I2C address is 0x53, connect SDO pin to GND and I2C address will be 0x52

  DFRobot_ENS160_I2C ENS160(&Wire, /*I2CAddr*/ 0x53);
#else
  /**
   * Set up digital pin according to the on-board pin connected with SPI chip-select pin
   * csPin Available Pins. For example: ESP32&ESP8266(D3), m0(6)
   */
  uint8_t csPin = D3;
  DFRobot_ENS160_SPI ENS160(&SPI, csPin);
#endif

////////////// 센서 핀 위치 설정 //////////////////

       /// INPUT 센서

int forcepin = A1;


       /// OUTPUT 장치

int BACKLIGHT = 8;  ///// 후미등 input
int speakerPin = 9; ///// 부저스피커 input
int tones[]={261,277,311}; // 연주할 톤의 진동수.
int delays = 500;
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
  
  while( NO_ERR != ENS160.begin() ){
    Serial.println("Air quality sensor failed.");
    delay(delays);
  }

  // Serial.println("Adafruit VL53L0X ");
  if (!lox.begin()) {
     Serial.println(F("Distance Sensor failed."));
     while(1);
   }
  ENS160.setPWRMode(ENS160_STANDARD_MODE); 
  ENS160.setTempAndHum(/*temperature=*/25.0, /*humidity=*/50.0);
}


void loop() {

  VL53L0X_RangingMeasurementData_t measure;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
  int force = analogRead(forcepin); // 압전센서의 측정값
  uint16_t ECO2 = ENS160.getECO2(); // CO2 농도 측정값
  Serial.print("Carbon dioxide equivalent concentration : ");Serial.print(ECO2);Serial.println(" ppm");

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    
    if (measure.RangeMilliMeter >= HEAD & force <= GRIP ) {

      Serial.print("distance : "); Serial.print(measure.RangeMilliMeter); Serial.print(", force : "); Serial.print(force); Serial.println(" - WAKE UP");

      digitalWrite(BACKLIGHT,HIGH);  // 후미등 껐다 켜기
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

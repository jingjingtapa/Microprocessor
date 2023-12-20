#include "Adafruit_VL53L0X.h" //적외선 거리 측정센서, I2C addr = 0x29
#include <DFRobot_ENS160.h> //CO2 측정센서, I2C addr = 0x53
#include <Wire.h> // I2C 통신


Adafruit_VL53L0X lox = Adafruit_VL53L0X();
DFRobot_ENS160_I2C ENS160(&Wire, /*I2CAddr*/0x53);


////////////// 아날로그 핀 위치 설정 //////////////////
int forcepin = A1; // 압전센서
int jodopin = A0; // 조도센서
int delays = 30; // delay 조절
//////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  while (! Serial);
  
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
  int ECO2 = ENS160.getECO2(); // CO2 농도 측정값
  int brightness = analogRead(jodopin); // 조도센서 측정값
  int distance = measure.RangeMilliMeter; // 적외선 거리 센서 측정값
  
  ////////////    측정 데이터 출력
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data 적외선 센서에서 부정확한 데이터를 거름
    Serial.print(distance); 
    Serial.print("/"); 
    Serial.print(force);
    Serial.print("/"); 
    Serial.print(ECO2); 
    Serial.print("/"); 
    Serial.print(brightness);
    Serial.println("/");
    delay(delays);
  
  }
}
#include <Stepper.h>
#include <Adafruit_NeoPixel.h>
#define LED_COUNT1 11
#define LED_COUNT2 8
#define BRIGHTNESS 255
const int stepsPerRevolution = 512;


// 아웃풋 핀, 변수 세팅
int BUZZER = 4;
int LED_PIN1=5;
int LED_PIN2=6;
int sleep;
int tones[]={261,277,311};

Stepper myStepper(stepsPerRevolution,11,9,10,8);
Adafruit_NeoPixel strip1(LED_COUNT1, LED_PIN1, NEO_GRB + NEO_KHZ800); // 전조등
Adafruit_NeoPixel strip2(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800); // 실내 야간등

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // 줄led 세팅
  strip1.begin();
  strip1.setBrightness(BRIGHTNESS);
  strip1.show();
  strip2.begin();
  strip2.setBrightness(BRIGHTNESS);
  strip2.show();

  // 부저 세팅
  pinMode(BUZZER,OUTPUT);

  myStepper.setSpeed(60);

}

void loop() {

  while (Serial.available()){
    char c = Serial.read();
    Serial.println(c);

    // 상황 1
    if(c == '1'){

      for (int i = 0; i < LED_COUNT1; i++) {
        strip1.setPixelColor(i, 255, 0, 0);
      }
      strip1.show();
      
      tone(BUZZER,tones[0]);

    }




    
    
    if(c=='0') {

      noTone(BUZZER);

      for (int i = 0; i < LED_COUNT1; i++) {
        strip1.setPixelColor(i, 0, 0, 0);
      }
      strip1.show();

      for (int i = 0; i < LED_COUNT2; i++) {
        strip2.setPixelColor(i, 0, 0, 0);
      }
      strip2.show();

    }

    if(c=='2') {
      for (int i = 0; i < LED_COUNT2; i++) {
        strip2.setPixelColor(i, 255, 255, 255);
      }
      strip2.show();
    }
    
    if(c=='3') {
      for (int i = 0; i < LED_COUNT2; i++) {
        strip2.setPixelColor(i, 255, 255, 255);
      }
      strip2.show();

      for (int i = 0; i < LED_COUNT1; i++) {
        strip1.setPixelColor(i, 255, 0, 0);
      }
      strip1.show();
      
      tone(BUZZER,tones[0]);

      delay(100);

      noTone(BUZZER);

      for (int i = 0; i < LED_COUNT1; i++) {
        strip1.setPixelColor(i, 0, 0, 0);
      }
      strip1.show();

      delay(100);



    }

    if(c=='4') {
      noTone(BUZZER);

      for (int i = 0; i < LED_COUNT1; i++) {
        strip1.setPixelColor(i, 0, 0, 0);
      }
      strip1.show();

      for (int i = 0; i < LED_COUNT2; i++) {
        strip2.setPixelColor(i, 0, 0, 0);
      }
      strip2.show();

      delay(3000);
    }

    if(c=='o'){
      myStepper.step(-stepsPerRevolution);

    }

    if(c=='c'){
      myStepper.step(stepsPerRevolution);
    }



  }

}

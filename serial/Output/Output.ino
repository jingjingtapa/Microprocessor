#include <Stepper.h>
#include <Adafruit_NeoPixel.h>
#define LED_COUNT 30
#define BRIGHTNESS 255
const int stepsPerRevolution = 2048;

int BUZZER = 6;
int LED_pin=7;
int sleep;
int tones[]={261,277,311};
Stepper myStepper(stepsPerRevolution,11,9,10,8);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  pinMode(BUZZER,OUTPUT);
  //pinMode(MOTOR,OUTPUT);
  pinMode(LED,OUTPUT);
  myStepper.setSpeed(14);
}

void loop() {
  int color_r = 255;  // RED
  int color_g = 255;    // GREEN
  int color_b = 10;  // BLUE
  while (Serial.available()){
    char c = Serial.read();
    Serial.println(c);
    if(c == '1'){
      for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, 180, 180, 180);
      }
      strip.show();
      tone(BUZZER,tones[0]);

    }
    
    else {
      digitalWrite(LED_pin,LOW);
      noTone(BUZZER);
    }
  }
  if(ECO2 value >=300){
    for (int i = 0; i < 3; ++i) {
      myStepper.step(-stepsPerRevolution);
      delay(500);
    }
  }
}





    



  
 


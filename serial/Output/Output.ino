#output 코드에서 출력 모터 추가 코드
#include <Stepper.h>
const int stepsPerRevolution = 2048;
int BUZZER = 6;
int LED = 7;
//int MOTOR = 10;
int sleep;
int tones[]={261,277,311};
Stepper myStepper(stepsPerRevolution,11,9,10,8);
//int CO2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(BUZZER,OUTPUT);
  //pinMode(MOTOR,OUTPUT);
  pinMode(LED,OUTPUT);
  myStepper.setSpeed(14);
}

void loop() {
  while (Serial.available()){
    char c = Serial.read();
    Serial.println(c);
    if(c == '1'){
     digitalWrite(LED,HIGH);

     tone(BUZZER,tones[0]);

    }
    
    else {
      digitalWrite(LED,LOW);
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




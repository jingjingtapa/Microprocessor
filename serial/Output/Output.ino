int BUZZER = 6;
int LED = 7;
//int MOTOR = 10;
int sleep;
int tones[]={261,277,311};
//int CO2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(BUZZER,OUTPUT);
  //pinMode(MOTOR,OUTPUT);
  pinMode(LED,OUTPUT);

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
 
}

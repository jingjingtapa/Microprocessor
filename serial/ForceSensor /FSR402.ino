int sensor = A3;   // 압전 센서핀을 A2번으로 설정
int led = 11;      // LED핀을 11번으로 설정
 
void setup(){
  Serial.begin(9600);    //시리얼 통신, 속도는 9600
  pinMode(led, OUTPUT);  // LED 결과값으로 설정
}
 
void loop(){
  int val = analogRead(sensor);  //압전 센서의 데이터 받아오기
  if(val >120)             // 압전 센서의 데이터값으로 LED 제어
  {
    digitalWrite(led, HIGH);   
  }
  else
  {
    digitalWrite(led,LOW);
  }
}
 

char cmd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    cmd = Serial.read();

    if(cmd=='a'){
      Serial.println("아두이노:a");
      delay(100);

    }
    else if(cmd=="b"){
      Serial.println("아두이노:b");
      delay(100);
    }
  }
}

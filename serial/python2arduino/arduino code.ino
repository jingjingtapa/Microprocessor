int input_data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
    input_data = Serial.read();
  }

  if(input_data == '1')
  {
    digitalWrite(13, HIGH); // led_on
  }
  else if(input_data == '0')
  {
    digitalWrite(13, LOW); // led_off
  }
}

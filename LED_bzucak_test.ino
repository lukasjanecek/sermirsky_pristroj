void setup() {
  // put your setup code here, to run once:
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
 // tone(6, 2000, 2000);
digitalWrite(7, HIGH);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(2000);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(100);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(2000);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(100);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(2000);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(100);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, LOW);
delay(2000);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(100);
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
digitalWrite(3, HIGH);
delay(2000);
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(4, LOW);
digitalWrite(3, LOW);
delay(100);
/*
digitalWrite(6, HIGH);
digitalWrite(5, LOW);
delay(1000);

digitalWrite(6, LOW);
digitalWrite(5, HIGH);
delay(1000);

digitalWrite(6, LOW);
digitalWrite(5, LOW);
delay(1000);
*/
}

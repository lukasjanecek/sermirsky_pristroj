void setup() {
  // put your setup code here, to run once:
pinMode(A0, OUTPUT);
pinMode(A5, OUTPUT);
pinMode(A3, OUTPUT);
//pinMode(6, OUTPUT);
//pinMode(7, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  tone(A0, 2000, 2000);
  tone(A5, 2000, 2000);
analogWrite(A0, 1023);
delay(1000);
analogWrite(A0, 0);
analogWrite(A5, 1023);
delay(1000);
analogWrite(A5, 0);
delay(2000);
analogWrite(A0, 500);
delay(1000);
analogWrite(A0, 0);
analogWrite(A5, 500);
delay(1000);
analogWrite(A5, 0);
delay(2000);

analogWrite(A3, 500);
//tone(A0, 2000, 2000);
delay(3000);
analogWrite(A3, 0);
delay(2000);
analogWrite(A3, 500);
tone(A5, 3000, 2000);
delay(3000);
analogWrite(A3, 0);

/*,
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

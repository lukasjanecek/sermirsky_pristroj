int fleret, vesta, zasah;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2, HIGH);
pinMode(4, INPUT);
pinMode(7, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
//fleret = digitalRead(4);
zasah = digitalRead(2);

Serial.println("Vesta:");
Serial.println(vesta);
Serial.println("Zasah:");
Serial.println(zasah);
delay(1000);
}

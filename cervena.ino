#include <SoftwareSerial.h>

SoftwareSerial bluetoothP(10, 11);  //RX,TX

int fleret, vesta, zasah;

int LEDindikace = 9;
int platny  = 3;
int neplatny = 5;
int bzucak = 7;

void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetoothP.begin(9600);  
 
    Serial.println("");
    Serial.println("nastavit NL & CR v serial monitoru");
    Serial.println("Ready");
    Serial.println(""); 

    bluetoothP.println("AT");
    delay(500);
    bluetoothP.println("AT+DEFAULT");
    delay(500);
    bluetoothP.println("AT+ROLE0");
    delay(500);
    bluetoothP.println("AT+IMME1");
    delay(500);
    bluetoothP.println("AT+NAME==SLAVE2");
    delay(500);
    bluetoothP.println("AT+LADDR");
    delay(500);
    
    pinMode(A2, INPUT);
    pinMode(A4, INPUT);

    pinMode(LEDindikace, OUTPUT);
    digitalWrite(LEDindikace, LOW);
    pinMode(platny, OUTPUT);
    digitalWrite(platny, LOW);
    pinMode(neplatny, OUTPUT);
    digitalWrite(neplatny, LOW);
    pinMode(bzucak, OUTPUT);
    digitalWrite(bzucak, LOW);
    
}
 
void loop() 
{
    vesta = analogRead(A2);
    fleret = analogRead(A4);

    //vypis hodnot
    Serial.print("Vesta:");
    Serial.println(vesta);
    Serial.print("Fleret:");
    Serial.println(fleret);
    delay(1000);
    
    
    
    //rozliseni zasahu
    if (vesta=0) {  //bod L platny
    bluetoothP.write(2);
    }
    else if (vesta<320 &&vesta>75) {  //bod L neplatny
    bluetoothP.write(3);  
    } 
    else if (fleret>90 && fleret<vesta) {  //bod P platny
    bluetoothP.write(4);
    digitalWrite(3, HIGH);
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(3, LOW);
    digitalWrite(7, LOW); 
    }
    else if (fleret>90 && fleret<vesta) {  //bod P neplatny
    bluetoothP.write(5);
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);  
    }
    else {
    bluetoothP.write(1);
    }
    
    //blikání LED (indikace connected) 
    if (bluetoothP.read()>1) {
    digitalWrite(LEDindikace, HIGH);
    delay(2000);
    digitalWrite(LEDindikace, LOW);
    }
    else {
    digitalWrite(LEDindikace, HIGH);
    }    
}

//modra
#include <SoftwareSerial.h>

SoftwareSerial bluetoothP(10, 11);  //TX, RX

int fleret, vesta, zasah;

int LEDindikace = 9;

void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetoothP.begin(9600);  
 
    Serial.println("");
    Serial.println("nastavit NL & CR v serial monitoru!!!");
    Serial.println("Jedem");
    Serial.println(""); 
    
    bluetoothP.println("AT");
    delay(500);
    bluetoothP.println("AT+DEFAULT");
    delay(500);
    bluetoothP.println("AT+ROLE0");
    delay(500);
    bluetoothP.println("AT+IMME1");
    delay(500);
    bluetoothP.println("AT+LADDR");
    delay(500);
    bluetoothP.println("AT+NAME=SLAVE1");
    delay(500);
    
    pinMode(A2, INPUT);
    pinMode(A4, INPUT);

    pinMode(LEDindikace, OUTPUT);
    digitalWrite(LEDindikace, LOW);
    
}
 
void loop() 
{
    fleret = analogRead(A2);
    vesta = analogRead(A4);

    //vypis hodnot
    Serial.print("Vesta:");
    Serial.println(vesta);
    Serial.print("Fleret:");
    Serial.println(fleret);
    delay(1000);
    
    //blikání LED (indikace connected) 
    if (bluetoothP.available()<1) {
    digitalWrite(LEDindikace, HIGH);
    delay(2000);
    digitalWrite(LEDindikace, LOW);
    }
    else {
    digitalWrite(LEDindikace, HIGH);
    }

    //rozliseni zasahu
    if (vesta=0) {  //bod L platny
      bluetoothP.write(2);
    }
    else if (vesta>0) {  //bod L neplatny
    bluetoothP.write(3);  
    } 
    else if (fleret>0) {  //bod P platny
    bluetoothP.write(4);  
    }
    /*else if (fleret=0 && vesta>94) {  //bod P neplatny      useless navíc, zbytečně plete kod
    bluetoothP.write(5);  
    }*/ 
    else {
    bluetoothP.write(1);
    }
     
}

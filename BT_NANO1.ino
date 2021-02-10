#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);  //TX, RX

int fleret, vesta, zasah;

int LEDindikace = 9;

void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetooth.begin(9600);  
 
    Serial.println("");
    Serial.println("nastavit NL & CR v serial monitoru!!!");
    Serial.println("Jedem");
    Serial.println(""); 
    
    bluetooth.println("AT");
    delay(500);
    bluetooth.println("AT+DEFAULT");
    delay(500);
    bluetooth.println("AT+ROLE0");
    delay(500);
    bluetooth.println("AT+IMME1");
    delay(500);
    bluetooth.println("AT+LADDR");
    delay(500);
    bluetooth.println("AT+NAME=SLAVE1");
    delay(500);
    
    pinMode(A2, INPUT);
    pinMode(A4, INPUT);

    pinMode(LEDindikace, OUTPUT);
    digitalWrite(LEDindikace, LOW);
}
 
void loop() 
{
    digitalWrite(LEDindikace, HIGH);
    
    // čeká na příchozí komunikaci a pak ji napíše do sériového monitoru
    if ( bluetooth.available() )   {  Serial.write( bluetooth.read() );  }
 
    // čeká na vstup a posílá ho do spárovaného zařízení 
    if ( Serial.available() )       {  bluetooth.write( Serial.read() );  }

    vesta = analogRead(A2);
    fleret = analogRead(A4);

    Serial.println("Vesta:");
    Serial.println(vesta);
    Serial.println("Fleret:");
    Serial.println(fleret);
    delay(1000);

    if (vesta>0 && fleret==0) {
      bluetooth.write(1);
    }
    
    if (vesta==0 && fleret==0) {
      bluetooth.write(2);
    }
}

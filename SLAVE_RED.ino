//cervena
#include <SoftwareSerial.h>

SoftwareSerial bluetoothL(10, 11);  //RX,TX

int fleret, vesta, zasah;

int LEDindikace = 9;

void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetoothL.begin(9600);  
 
    Serial.println("");
    Serial.println("nastavit NL & CR v serial monitoru");
    Serial.println("Ready");
    Serial.println(""); 

    bluetoothL.println("AT");
    delay(500);
    bluetoothL.println("AT+DEFAULT");
    delay(500);
    bluetoothL.println("AT+ROLE0");
    delay(500);
    bluetoothL.println("AT+IMME1");
    delay(500);
    bluetoothL.println("AT+NAME==SLAVE2");
    delay(500);
    bluetoothL.println("AT+LADDR");
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
    if (bluetoothL.available()<1) {
    digitalWrite(LEDindikace, HIGH);
    delay(2000);
    digitalWrite(LEDindikace, LOW);
    }
    else {
    digitalWrite(LEDindikace, HIGH);
    }

    //rozliseni zasahu
    if (fleret>0) {  //bod L platny
    bluetoothL.write(2);
    }
    /*else if (fleret>0) {  //bod L neplatny      useless navíc, zbytečně plete kod
    bluetoothL.write(3);  
    } */ 
    else if (vesta<10) {  //bod P platny
    bluetoothL.write(4); 
    }
    else if (vesta>0) {  //bod P neplatny
    bluetoothL.write(5);  
    }
    else {
    bluetoothL.write(1);
    }
        
}

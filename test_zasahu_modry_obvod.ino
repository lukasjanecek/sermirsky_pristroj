#include <SoftwareSerial.h>

SoftwareSerial bluetoothL(10, 11);  //TX, RX

int fleret, vesta, zasah;

int LEDindikace = 9;
int platny  = 3;
int neplatny = 5;
int bzucak = 7;


void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetoothL.begin(115200);  
 
    Serial.println("");
    Serial.println("nastavit NL & CR v serial monitoru!!!");
    Serial.println("Jedem");
    Serial.println(""); 
    
    bluetoothL.println("AT");
    delay(500);
    bluetoothL.println("AT+DEFAULT");
    delay(500);
    bluetoothL.println("AT+ROLE0");
    delay(500);
    bluetoothL.println("AT+IMME1");
    delay(500);
    bluetoothL.println("AT+LADDR");
    delay(500);
    bluetoothL.println("AT+NAME=SLAVE1");
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
    if (fleret>0 && ((vesta<(fleret+60) || vesta>(fleret-60) ) ) ) {  //bod L platny
      bluetoothL.write(2);
      digitalWrite(3, HIGH);
      digitalWrite(7, HIGH);
      delay(2000);
      digitalWrite(3, LOW);
      digitalWrite(7, LOW);
    }
    else if (fleret>0 && fleret<vesta ) {  //bod L neplatny
    bluetoothL.write(3);
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
    delay(2000);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);  
    } 
    else if (fleret=0 && vesta>70 && vesta<90) {  //bod P platny
    bluetoothL.write(4);  
    }
    else if (fleret=0 && vesta>94) {  //bod P neplatny
    bluetoothL.write(5);  
    }
    else {
    bluetoothL.write(1);
    }
    
    //blikání LED (indikace connected) 
    if (bluetoothL.read()>1) {
    digitalWrite(LEDindikace, HIGH);
    delay(2000);
    digitalWrite(LEDindikace, LOW);
    }
    else {
    digitalWrite(LEDindikace, HIGH);
    } 
}

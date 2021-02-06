#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);  //TX, RX
int LED = 8;
 
void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetooth.begin(9600); 
     
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    Serial.println("");
    Serial.println("nastavit Both NL & CR v sériovém monitoru");
    Serial.println("Jedem");
    Serial.println("");
    
    bluetooth.println("AT");
    delay(200);
    bluetooth.println("AT+ROLE0");
    delay(200);
    bluetooth.println("AT+IMME1");
    delay(200);
    bluetooth.println("AT+NAME==SLAVE2");
    delay(200);
    bluetooth.println("AT+LADDR");
    delay(200);
}
 
void loop() 
{    
    if (bluetooth.available()<0) {
    bluetooth.println("AT+DEFAULT");
    bluetooth.println("AT+NAME==SLAVE2");
    bluetooth.println("AT+IMME1");
    }
    
    // čeká na příchozí komunikaci a pak ji napíše do sériového monitoru
    if (bluetooth.available()) {  
    Serial.write(bluetooth.read());  
    if (Serial.write(bluetooth.read()) == 1){
        digitalWrite(LED, LOW);
        delay(5000);
        digitalWrite(LED, HIGH);  
        delay(5000);
        digitalWrite(LED, LOW);
      }
      }
    
    // čeká na vstup a posílá ho do spárovaného zařízení
    if (Serial.available()) {  
    bluetooth.write(Serial.read());  
    }
  
    
   
    /*if (bluetooth.available()>0) {
    bluetooth.write(Serial.read());
    
    bluetooth.println(bluetooth.read());
      if (bluetooth.read() == "1"){
        digitalWrite(LED, HIGH);  
      }
      else if (bluetooth.read() == "2"){
        digitalWrite(LED, LOW);  
      }  
    }*/
}

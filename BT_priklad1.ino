#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);  //RX,TX
int LED = 9;

void setup() 
{
    Serial.begin(9600);     // komunikace s host zařízením
 
    // Start software serial komunikaci se spojeným prvkem
    bluetooth.begin(9600);  

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    Serial.println("");
    Serial.println("nastavit Both NL & CR v sériovém monitoru");
    Serial.println("Leeets goo");
    Serial.println(""); 
    
    bluetooth.println("AT");
    delay(500);
    bluetooth.println("AT+ROLE1");
    delay(500);
    bluetooth.println("AT+IMME1");
    delay(500);
    bluetooth.println("AT+NAME=MASTER");
    delay(500);
    bluetooth.println("AT+CONA0013AA00C2B8");
    delay(500);
    
}
 
void loop() 
{   
    int b;
    
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if (bluetooth.available()) {  
    Serial.write(bluetooth.read());  
    }

    // listen for user input and send it to the ESP8266
    if (Serial.available()) {  
    bluetooth.write(Serial.read());  
    }
      
     
    
   /* if (bluetooth.available()>0) {
    b = bluetooth.write(Serial.read());
    bluetooth.print("a:");
    bluetooth.println(bluetooth.write(Serial.read()));

      if (b == "1"){
        digitalWrite(LED, HIGH);  
      }
      else if (b == "2"){
        digitalWrite(LED, LOW);  
      }  
    }*/
  
}

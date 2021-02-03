#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);  //RX,TX
int LED = 8;


 
void setup() 
{
    Serial.begin(9600);     // komunikace s host zařízením
 
    // Start software serial komunikaci se spojeným prvkem
    bluetooth.begin(9600); 
     
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    Serial.println("");
    Serial.println("nastavit Both NL & CR v sériovém monitoru");
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
    bluetooth.println("AT+NAME==SLAVE");
    delay(500);
    /*bluetooth.println("AT+LADDR");
    delay(500);*/
    
}
 
void loop() 
{
    int a;
    
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if (bluetooth.available()) {  
    Serial.write(bluetooth.read());  
    }

    // listen for user input and send it to the ESP8266
    if (Serial.available()) {  
    bluetooth.write(Serial.read());  
    }

   /* if (bluetooth.available()>0) {
    a = bluetooth.write(Serial.read());
    bluetooth.print("b:");
    bluetooth.println(bluetooth.write(Serial.read()));
    
      if (a == '1'){
        digitalWrite(LED, HIGH);  
      }
      else if (a == '2'){
        digitalWrite(LED, LOW);  
      }  
    }  */
}

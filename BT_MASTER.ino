#include <SoftwareSerial.h>

SoftwareSerial bluetooth1(5, 6);    //TX, RX
//SoftwareSerial bluetooth2(10, 11);  //TX, RX

int LED = 8;


void setup() 
{
    Serial.begin(9600);     
 
    // Start software serial komunikaci se spárovaným zařízením
    bluetooth1.begin(9600);
    //bluetooth2.begin(9600);  

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    Serial.println("");
    Serial.println("nastavit NL & CR v serial monitoru!!!");
    Serial.println("Bomby");
    Serial.println("");

    /*bluetooth2.println("AT");
    delay(500);
    bluetooth2.println("AT+ROLE1");
    delay(500);
    bluetooth2.println("AT+IMME1");
    delay(500);
    bluetooth2.println("AT+NAME=MASTER2");
    delay(500);
    bluetooth2.println("AT+CONA882583F062E2");
    delay(500);*/
    
    bluetooth1.println("AT");
    delay(200);
    bluetooth1.println("AT+ROLE1");
    delay(200);
    bluetooth1.println("AT+IMME1");
    delay(200);
    bluetooth1.println("AT+NAME=MASTER1");
    delay(2000);
    bluetooth1.println("AT+CONA0013AA00C2B8");
    delay(200);
}
 
void loop() 
{    
      // čeká na příchozí komunikaci a pak ji napíše do sériového monitoru
      if (bluetooth1.available() )   {
      Serial.write(bluetooth1.read() );  
      if (Serial.write(bluetooth1.read()) == 1){
        digitalWrite(LED, LOW);
        delay(5000);
        digitalWrite(LED, HIGH);  
        delay(5000);
        digitalWrite(LED, LOW);
      }
      }
      
 
      // čeká na vstup a posílá ho do spárovaného zařízení
      if ( Serial.available() )       {  bluetooth1.write( Serial.read() );  }

      /*bluetooth1.write('1');
      delay(10000);
      bluetooth1.write('0');
      delay(1000);*/
      
    
    
    /*// čeká na příchozí komunikaci a pak ji napíše do sériového monitoru
    if ( bluetooth2.available() )   {  Serial.write( bluetooth2.read() );  }
 
    // čeká na vstup a posílá ho do spárovaného zařízení
    if ( Serial.available() )       {  bluetooth2.write( Serial.read() );  }*/

    /*if (bluetooth1.available()>0) {
    bluetooth1.write(Serial.read());
    bluetooth1.println(bluetooth1.read());
      if (bluetooth1.read() == "1"){
        digitalWrite(LED, HIGH);  
      }
      else if (bluetooth1.read() == "2"){
        digitalWrite(LED, LOW);  
      }  
    }

    
    if (bluetooth2.available()>0) {
    bluetooth2.write(Serial.read());
    bluetooth2.println(bluetooth2.read());
      if (bluetooth2.read() == "1"){
        digitalWrite(LED, HIGH);  
      }
      else if (bluetooth2.read() == "2"){
        digitalWrite(LED, LOW);  
      }  
    }*/
    
}

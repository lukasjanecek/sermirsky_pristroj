#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  //RX,TX
SoftwareSerial bluetooth(10, 11);
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH

// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266

int a;

 
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    mySerial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");
    /*bluetooth.println("");
    bluetooth.println("Remember to to set Both NL & CR in the serial monitor.");
    bluetooth.println("Ready");
    bluetooth.println("Ahoj, já jsem UNO");*/
    //Serial.println("Pricti k hodnote a cislo");
    //bluetooth.println("Pricti k hodnote a cislo:");    
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  mySerial.write( Serial.read() );  }
/*
    while(bluetooth.available()>0) {
  a += bluetooth.parseInt(); 
  }
  while (Serial.available()>0) {
    a += Serial.parseInt();
  }
  delay(1000);
  Serial.println(a);
  bluetooth.println(a);
  */
}

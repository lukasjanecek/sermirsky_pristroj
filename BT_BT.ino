#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);  //RX,TX

int a;
 
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    bluetooth.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println(""); 
    
    //bluetooth.println("No nazdar");
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( bluetooth.available() )   {  Serial.write( bluetooth.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  bluetooth.write( Serial.read() );  }
}

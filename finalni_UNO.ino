//knihovny pro OLED
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//knihovna pro IR
#include <IRremote.h>

//knihovna BT
#include <SoftwareSerial.h>

// definování pinu přijímače IR
int const IRpin = 2;
IRrecv irrecv(IRpin);
// uložení signálu do proměné "results"
decode_results results;

//BT
SoftwareSerial bluetooth1(5, 6);    //TX, RX
SoftwareSerial bluetooth2(10, 11);  //TX, RX

//proměnné OLED
//čas
int s=0;
int m=3;
//body
int BodyL=0;
int BodyP=0;

//LED
int LEDbila1 = A0;
int LEDbila2 = A1;
int LEDbila3 = A2;
int LEDbila4 = A3;
int LEDcervena1 = 4;
int LEDcervena2 = 3;
int LEDzelena1 = 13;
int LEDzelena2 = 12;
int bzucak = 9;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//IR
// start přijímače
irrecv.enableIRIn(); 



//OLED
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed"));
}
delay(2000);
display.clearDisplay();

//BT
bluetooth1.begin(9600);
bluetooth2.begin(9600);  


//LED
pinMode(LEDbila1, OUTPUT);
digitalWrite(LEDbila1, LOW);

pinMode(LEDbila2, OUTPUT);
digitalWrite(LEDbila2, LOW);

pinMode(LEDbila3, OUTPUT);
digitalWrite(LEDbila3, LOW);

pinMode(LEDbila4, OUTPUT);
digitalWrite(LEDbila4, LOW);

pinMode(LEDcervena1, OUTPUT);
digitalWrite(LEDcervena1, LOW);

pinMode(LEDcervena2, OUTPUT);
digitalWrite(LEDcervena2, LOW);

pinMode(LEDzelena1, OUTPUT);
digitalWrite(LEDzelena1, LOW);

pinMode(LEDzelena2, OUTPUT);
digitalWrite(LEDzelena2, LOW);

pinMode(bzucak, OUTPUT);
digitalWrite(bzucak, LOW);

    
Serial.println("");
Serial.println("nastavit NL & CR v serial monitoru!!!");
Serial.println("Bomby");
Serial.println("");

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

bluetooth2.println("AT");
delay(500);
bluetooth2.println("AT+ROLE1");
delay(500);
bluetooth2.println("AT+IMME1");
delay(500);
bluetooth2.println("AT+NAME=MASTER2");
delay(500);
bluetooth2.println("AT+CONA882583F062E2");
delay(500);
    
}

void loop() {
  // put your main code here, to run repeatedly:

//IR
// pokud obdržíš signál, tak jeho hodnotu vypiš v DEC soustavě (desítková)
  if (irrecv.decode(&results)) 
    {
      Serial.println(results.value, DEC); 
      // obdrž další hodnotu
      irrecv.resume(); 
      // počkej 1s
      delay(1000);
    }

switch (results.value) {

  case 3810010651: //1 //+1 na leve strane
  Serial.println("1");
  BodyL=BodyL+1;
  delay (2000);
  break;
  
  case 5316027: //2 // //set casu (+1 minuta za zmacknuti)
  Serial.println("2");
  m=1;
  s=0;
  break;
  
  case 4001918335: //3 //+1 na prave strane
  Serial.println("3");
  BodyP=BodyP+1;
  delay(2000);
  break;
  
  case 1386468383: //4 //-1 na leve strane
  Serial.println("4");
  BodyL=BodyL-1;
  delay(2000);
  break;
  
  case 3622325019: //5 //reset na default 3 minuty //rearm
  Serial.println("5");
  delay(1000);
  m=3;
  s=0;
  BodyL=0;
  BodyP=0;
  delay(2000);
  break;
  
  case 553536955: //6 //-1 na prave strane
  Serial.println("6");
  BodyP=BodyP-1;
  delay(2000);
  break;
  
  case 4034314555: //7
  Serial.println("7");
  break;
  
  case 2747854299: //8
  Serial.println("8");
  break;
  
  case 3855596927: //9
  Serial.println("9");
  break;
  
  case 3238126971: //*
  Serial.println("*");
  break;
  
  case 2538093563: //0
  Serial.println("0");
  break;
  
  case 4039382595: //#
  Serial.println("#");
  break;
  
  case 2351064443: //sipka doleva
  Serial.println("sipka doleva");
  break;
  
  case 71952287: //sipka doprava
  Serial.println("sipka doprava");
  break;
  
  case 1033561079: //sipka nahoru
  Serial.println("sipka nahoru");
  break;
  
  case 465573243: //sipka dolu
  Serial.println("sipka dolu");
  break;
  
  case 1217346747: //OK //stop/play
  Serial.println("KO");
  s=s+1;
  break; 
  }
  
//OLED
display.clearDisplay();
display.setTextColor(WHITE);
display.setCursor(0,0);
display.setTextSize(1);

//tisk bodů
display.setTextSize(2);
display.print(BodyL);
display.print("  ");
display.print(m);
display.print(":");
display.print(s);
display.print("  ");
display.print(BodyP);
display.display();
delay(50);

//stopky
s=s-1;
if (s==-1) {
  s=59;
  m=m-1;
}

if(m==0 && s==0){
display.clearDisplay();
display.setCursor(0,0);
display.setTextSize(2);
display.println("\n");
display.println("_KONEC_");
display.display();
delay(5000);
s=0;
m=3;
BodyL=0;
BodyP=0;
delay(1000);
}

//BT
// čeká na příchozí komunikaci a pak ji napíše do sériového monitoru
if (bluetooth1.available() )   {
  Serial.write(bluetooth1.read() );  
    if (Serial.write(bluetooth1.read()) == 1){
      digitalWrite(LEDbila1, HIGH);
      digitalWrite(LEDbila2, HIGH);
      digitalWrite(bzucak, HIGH);
      delay(3000);
      digitalWrite(LEDbila1, LOW);
      digitalWrite(LEDbila2, LOW);
      digitalWrite(bzucak, LOW); 
    }
    if (Serial.write(bluetooth1.read()) == 2){
      digitalWrite(LEDzelena1, HIGH);
      digitalWrite(LEDzelena2, HIGH);
      digitalWrite(bzucak, HIGH);
      delay(3000);
      digitalWrite(LEDzelena1, LOW);
      digitalWrite(LEDzelena2, LOW);
      digitalWrite(bzucak, LOW); 
    }
}
      
if (bluetooth2.available() )   {
  Serial.write(bluetooth2.read() );  
    if (Serial.write(bluetooth2.read()) == 1){
      digitalWrite(LEDbila3, HIGH);
      digitalWrite(LEDbila4, HIGH);
      digitalWrite(bzucak, HIGH);
      delay(3000);
      digitalWrite(LEDbila3, LOW);
      digitalWrite(LEDbila4, LOW);
      digitalWrite(bzucak, LOW);
    }
    if (Serial.write(bluetooth1.read()) == 2){
      digitalWrite(LEDcervena1, HIGH);
      digitalWrite(LEDcervena2, HIGH);
      digitalWrite(bzucak, HIGH);
      delay(3000);
      digitalWrite(LEDcervena1, LOW);
      digitalWrite(LEDcervena2, LOW);
      digitalWrite(bzucak, LOW); 
    }
}

if (bluetooth1.available() && bluetooth2.available()) {
  Serial.write(bluetooth1.read() );
  Serial.write(bluetooth2.read() );

  if (Serial.write(bluetooth1.read()==1) && Serial.write(bluetooth2.read()==1) ) {
    digitalWrite(LEDbila1, HIGH);
      digitalWrite(LEDbila2, HIGH);
      digitalWrite(LEDbila3, HIGH);
      digitalWrite(LEDbila4, HIGH);
      digitalWrite(bzucak, HIGH);
      delay(3000);
      digitalWrite(LEDbila1, LOW);
      digitalWrite(LEDbila2, LOW);
      digitalWrite(LEDbila3, LOW);
      digitalWrite(LEDbila4, LOW);
      digitalWrite(bzucak, LOW);
  }
  if (Serial.write(bluetooth1.read()==2) && Serial.write(bluetooth2.read()==2) ) {
    digitalWrite(LEDzelena1, HIGH);
      digitalWrite(LEDzelena2, HIGH);
      digitalWrite(LEDcervena1, HIGH);
      digitalWrite(LEDcervena2, HIGH);
      digitalWrite(bzucak, HIGH);
      delay(3000);
      digitalWrite(LEDzelena1, LOW);
      digitalWrite(LEDzelena2, LOW);
      digitalWrite(LEDcervena1, LOW);
      digitalWrite(LEDcervena2, LOW);
      digitalWrite(bzucak, LOW);
  }
  
}

 // čeká na vstup a posílá ho do spárovaného zařízení
      if ( Serial.available() )       {  bluetooth1.write( Serial.read() );  }
      if ( Serial.available() )       {  bluetooth2.write( Serial.read() );  }
}

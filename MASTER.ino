//knihovna pro IR
#include <IRremote.h>

//knihovna BT
#include <SoftwareSerial.h>

//knihovny pro OLED
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// definování pinu přijímače IR
int const IRpin = 2;
IRrecv irrecv(IRpin);
// uložení signálu do proměné "results"
decode_results results;

//BT
SoftwareSerial bluetoothP(3, 4);    //TX, RX
SoftwareSerial bluetoothL(10, 11);  //TX, RX

//proměnné OLED
//čas
int s=0;
int m=3;
//body
int BodyL=0;
int BodyP=0;

//LED
int LEDbila1 = 23;
int LEDbila2 = 24;
int LEDbila3 = 50;
int LEDbila4 = 53;
int LEDcervena1 = 42;
int LEDcervena2 = 45;
int LEDzelena1 = 31;
int LEDzelena2 = 32;
int bzucakRED = 9;
int bzucakGREEN = 8;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

//OLED
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed"));
}
delay(2000);
display.clearDisplay();

//IR
// start přijímače
irrecv.enableIRIn(); 

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
pinMode(bzucakRED, OUTPUT);
digitalWrite(bzucakRED, LOW);
pinMode(bzucakGREEN, OUTPUT);
digitalWrite(bzucakGREEN, LOW);

//BT
bluetoothL.begin(9600);
bluetoothP.begin(9600);  

bluetoothP.println("AT");
delay(500);
bluetoothP.println("AT+ROLE1");
delay(500);
bluetoothP.println("AT+IMME1");
delay(500);
bluetoothP.println("AT+NAME=MASTER1");
delay(500);
bluetoothP.println("AT+CONA0013AA00C2B8");//0013AA00C2B8
delay(500);

bluetoothL.println("AT");
delay(500);
bluetoothL.println("AT+ROLE1");
delay(500);
bluetoothL.println("AT+IMME1");
delay(500);
bluetoothL.println("AT+NAME=MASTER2");
delay(500);
bluetoothL.println("AT+CONA882583F062E2");//882583F062E2
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

//konec zapasu
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

//rozliseni zasahu, bylo by vhodné prakticky ověřit

if (bluetoothL.available() && bluetoothP.available()) {
  Serial.println(bluetoothL.read() );
  Serial.println(bluetoothP.read() );
  if (bluetoothL.read()==2 && bluetoothP.read()==2) {  //bod L platny
      digitalWrite(LEDzelena1, HIGH);
      digitalWrite(LEDzelena2, HIGH);
      digitalWrite(bzucakGREEN, HIGH);
      delay(3000);
      digitalWrite(LEDzelena1, LOW);
      digitalWrite(LEDzelena2, LOW);
      digitalWrite(bzucakGREEN, LOW);
  }
  if (bluetoothL.read()==2 && bluetoothP.read()==3) {  //bod L neplatny
      digitalWrite(LEDbila1, HIGH);
      digitalWrite(LEDbila2, HIGH);
      digitalWrite(bzucakGREEN, HIGH);
      delay(3000);
      digitalWrite(LEDbila1, LOW);
      digitalWrite(LEDbila2, LOW);
      digitalWrite(bzucakGREEN, LOW);
  }
  if (bluetoothL.read()==4 && bluetoothP.read()==4) {  //bod P platny
      digitalWrite(LEDcervena1, HIGH);
      digitalWrite(LEDcervena2, HIGH);
      digitalWrite(bzucakRED, HIGH);
      delay(3000);
      digitalWrite(LEDcervena1, LOW);
      digitalWrite(LEDcervena2, LOW);
      digitalWrite(bzucakRED, LOW);
  }
  if (bluetoothL.read()==5 && bluetoothP.read()==4) {  //bod P neplatny
      digitalWrite(LEDbila3, HIGH);
      digitalWrite(LEDbila4, HIGH);
      digitalWrite(bzucakRED, HIGH);
      delay(3000);
      digitalWrite(LEDbila3, LOW);
      digitalWrite(LEDbila4, LOW);
      digitalWrite(bzucakRED, LOW);
  }
  /*zasahy zaroven, NUTNO OTESTOVAT
  if ((bluetoothL.read()==2 && bluetoothP.read()==2) && (bluetoothL.read()==3 && bluetoothP.read()==3)) {  //bod P platny + bod L platny
  digitalWrite(LEDzelena1, HIGH);
  digitalWrite(LEDzelena2, HIGH);
  digitalWrite(bzucakGREEN, HIGH);
  digitalWrite(LEDcervena1, HIGH);
  digitalWrite(LEDcervena2, HIGH);
  digitalWrite(bzucakRED, HIGH);
  delay(3000);
  digitalWrite(LEDzelena1, LOW);
  digitalWrite(LEDzelena2, LOW);
  digitalWrite(bzucakGREEN, LOW);
  digitalWrite(LEDcervena1, LOW);
  digitalWrite(LEDcervena2, LOW);
  digitalWrite(bzucakRED, LOW);  
  }
  if ((bluetoothL.read()==2 && bluetoothP.read()==2) && (bluetoothL.read()==5 && bluetoothP.read()==5)) {  //bod P platny + bod L neplatny
  digitalWrite(LEDzelena1, HIGH);
  digitalWrite(LEDzelena2, HIGH);
  digitalWrite(bzucakGREEN, HIGH);
  digitalWrite(LEDbila3, HIGH);
  digitalWrite(LEDbila4, HIGH);
  digitalWrite(bzucakRED, HIGH);
  delay(3000);
  digitalWrite(LEDzelena1, LOW);
  digitalWrite(LEDzelena2, LOW);
  digitalWrite(bzucakGREEN, LOW);
  digitalWrite(LEDbila3, LOW);
  digitalWrite(LEDbila4, LOW);
  digitalWrite(bzucakRED, LOW);    
  }
  if ((bluetoothL.read()==3 && bluetoothP.read()==3) && (bluetoothL.read()==3 && bluetoothP.read()==3)) {  //bod P neplatny + bod L platny
  digitalWrite(LEDbila1, HIGH);
  digitalWrite(LEDbila2, HIGH);
  digitalWrite(bzucakGREEN, HIGH);
  digitalWrite(LEDcervena1, HIGH);
  digitalWrite(LEDcervena2, HIGH);
  digitalWrite(bzucakRED, HIGH);
  delay(3000);
  digitalWrite(LEDbila1, LOW);
  digitalWrite(LEDbila2, LOW);
  digitalWrite(bzucakGREEN, LOW);
  digitalWrite(LEDcervena1, LOW);
  digitalWrite(LEDcervena2, LOW);
  digitalWrite(bzucakRED, LOW);    
  }
  if ((bluetoothL.read()==3 && bluetoothP.read()==3) && (bluetoothL.read()==5 && bluetoothP.read()==5)) {  //bod P neplatny + bod L neplatny
  digitalWrite(LEDbila1, HIGH);
  digitalWrite(LEDbila2, HIGH);
  digitalWrite(bzucakGREEN, HIGH);
  digitalWrite(LEDbila3, HIGH);
  digitalWrite(LEDbila4, HIGH);
  digitalWrite(bzucakRED, HIGH);
  delay(3000);
  digitalWrite(LEDbila1, LOW);
  digitalWrite(LEDbila2, LOW);
  digitalWrite(bzucakGREEN, LOW);
  digitalWrite(LEDbila3, LOW);
  digitalWrite(LEDbila4, LOW);
  digitalWrite(bzucakRED, LOW);    
  }
}*/
}
}

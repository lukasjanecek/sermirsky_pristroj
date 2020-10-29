// Arduino Bluetooth modul HM-10

// nastavení propojovacích pinů Bluetooth 
#define RX 11
#define TX 10
// připojení knihovny SoftwareSerial
#include <SoftwareSerial.h>
// inicializace Bluetooth modulu z knihovny SoftwareSerial
SoftwareSerial bluetooth(TX, RX);
byte cislo, a=0, pom;

void setup() {
  // zahájení komunikace s Bluetooth modulem
  // skrze Softwarovou sériovou linku rychlostí 9600 baud
  bluetooth.begin(9600);
  bluetooth.println("Arduino zapnuto, test Bluetooth.");
  // komunikace po sériové lince rychlostí 9600 baud
  Serial.begin(9600);
  Serial.println("Arduino zapnuto, test Bluetooth.");
}

void loop() {
  // proměnná pro ukládání dat z Bluetooth modulu
  byte BluetoothData;
  // kontrola Bluetooth komunikace, pokud je dostupná nová
  // zpráva, tak nám tato funkce vrátí počet jejích znaků
  if (bluetooth.available() > 0) {
    // načtení prvního znaku ve frontě do proměnné
    BluetoothData=bluetooth.read();
    // dekódování přijatého znaku
  }
  
  Serial.println("Komunikace zacala \n");
  Serial.println("Az cislo presahne 100, tak komunikace skonci \n");
  
  do{
  Serial.print("Zadej cislo:");
  while(Serial.available()==0){}
  while(Serial.available()>0) {
  cislo = Serial.read()-48;
  pom = Serial.read();
  if (pom>='0' && pom <= '9') {
    cislo = (cislo*10) + (cislo-'0');
  }
  }
  Serial.println(cislo);
  a = cislo + 1;
  Serial.print("Nasledujici cislo:");
  Serial.println(a);
    } while (cislo<100 && a<100);
    
  Serial.println("Konec komunikace");
  
  // čas od spuštění Arduina
    bluetooth.print("Cas od spusteni Arduina: ");
    bluetooth.print(millis()/1000);
    bluetooth.println(" vterin.");    
  
  // krátká pauza mezi kontrolami komunikace Bluetooth modulu
  delay(100);
  
  /*
        // zde je ukázka načtení většího počtu informací,
        // po přijetí znaku 'b' tedy postupně tiskneme 
        // další znaky poslané ve zprávě
        bluetooth.print("Nacitam zpravu: ");
        BluetoothData=bluetooth.read();
        // v této smyčce zůstáváme do té doby,
        // dokud jsou nějaké znaky ve frontě
        while (bluetooth.available() > 0) {
          bluetooth.write(BluetoothData);
          Serial.write(BluetoothData);
          // krátká pauza mezi načítáním znaků
          delay(10);
          BluetoothData=bluetooth.read();
        }
        bluetooth.println();
       */
    
     /* osetreni podminkou, vsechny chyby 
      default:
        // v případě přijetí ostatních znaků
        // vytiskneme informaci o neznámé zprávě
        bluetooth.println("Neznamy prikaz.");
        */
    
  
  
}

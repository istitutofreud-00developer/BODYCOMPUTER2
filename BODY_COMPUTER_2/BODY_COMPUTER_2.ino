#include <LiquidCrystal_I2C.h>
#include  <Wire.h>
#include <Ultrasonic.h>
#include <DHT.h>
#define DHTPIN8
#define DHTTYPEDHT11
const int Posizione = 4;
const int FrecciaD = 12;
const int FrecciaS = 11;
const int Retronebbia = 13;
const int Cicalino = 9;
const int accensione=2;
const int Anababglianti = 3;
int Batteria = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // inserire valore esatto resistenza R1 (100K) 
float R2 = 10000.0; // inserire valore esatto resistenza R2 (10K) 
int value = 0;


const int button = 3;
int LuciPosizione;
int FrecciaDestra;
int FrecciaSinistra;
int LuceRetronebbia;
int buttonState;
int Luciauto;
int Lucianabaglianti;
int statobottone;


LiquidCrystal_I2C lcd(0x27,  20, 4);


Ultrasonic ultrasonic(7, 6);

DHT dht(8, DHT11);

byte Auto[] = {
  B00000,
  B00000,
  B00111,
  B01001,
  B11111,
  B01010,
  B00000,
  B00000
};

byte Completamento[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte PosizioneDX[] = {
  B00000,
  B00001,
  B11100,
  B10101,
  B10101,
  B11100,
  B00001,
  B00000
};


byte PosizioneSX[] = {
  B00000,
  B10000,
  B00111,
  B10101,
  B10101,
  B00111,
  B10000,
  B00000
};

byte Retronebia[] = {
  B00000,
  B00001,
  B01101,
  B10101,
  B01101,
  B00001,
  B00000,
  B00000
};

byte Battery[] = {
  B00000,
  B10001,
  B11111,
  B10001,
  B10001,
  B11111,
  B00000,
  B00000
};

byte Anabbaglianti[] = {
  B11110,
  B11101,
  B11100,
  B11110,
  B11101,
  B11100,
  B11110,
  B11101
};

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  

  lcd.print("   FIAT SEICENTO!");
  lcd.setCursor(0, 1);
  lcd.print("   BODY COMPUTER");
  lcd.setCursor(0, 3);
  lcd.print("VERSIONE: 2.0 D.ARD"); 
  delay(2000);
  lcd.clear();

lcd.createChar(0, Completamento);
lcd.createChar(1, Auto);
lcd.createChar(2, PosizioneDX);
lcd.createChar(3, PosizioneSX);
lcd.createChar(4, Retronebia);
lcd.createChar(5, Battery);
lcd.createChar(6, Anabbaglianti);

  
  pinMode(button, INPUT);
  pinMode(FrecciaD, INPUT);
  pinMode(FrecciaS, INPUT);
  pinMode(Posizione, INPUT);
  pinMode(Retronebbia, INPUT);
  pinMode(Batteria, INPUT);
  pinMode(Cicalino, OUTPUT);
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("FIAT 600 1.1 8v i.e. ");
  lcd.setCursor(0, 1);
  lcd.print("  M.P.I. 54CV 88Nm");
  lcd.setCursor(7, 2);
  lcd.print("EURO 4");
  delay(5000);
  lcd.clear();
  
delay(500);



}

void loop() {

    lcd.setCursor(0, 0);
    buttonState = digitalRead(button);
  if (buttonState==1){
    int distanza = ultrasonic.read();
     FrecciaDestra=digitalRead(FrecciaD);
     FrecciaSinistra=digitalRead(FrecciaS);
     LuceRetronebbia=digitalRead(Retronebbia);
     LuciPosizione=digitalRead(Posizione);

        vout = (value * 4.9) / 1024.0; 
   // inserire al posto di 5.0V l`uscita in volt tra i Pin 5V e GND del vostro Arduino
   
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;
} 


   if(FrecciaDestra==1){
  lcd.setCursor(18, 0);
  lcd.print("->");
  delay(100);
 }
    else {                                          
    lcd.setCursor(18, 0);
    lcd.print("  ");
  }  



   if(FrecciaSinistra==1){
  lcd.setCursor(0, 0);
  lcd.print("<-");
 }
    else {                                          
    lcd.setCursor(0, 0);
    lcd.print("  ");
  }  

    if(LuciPosizione==1){
  lcd.setCursor(2, 0);
  lcd.write(3);
  lcd.write(2);
 }
    else {                                          
    lcd.setCursor(2, 0);
    lcd.print("   ");
  }  

   if(LuceRetronebbia==1){
  lcd.setCursor(17, 0);
  lcd.write(4);
  
 }
    else {                                          
    lcd.setCursor(17, 0);
    lcd.print("  ");
}

if(vin>=13){
  lcd.setCursor(16, 0);
  lcd.write(5);
  
 }
    else {                                          
     lcd.setCursor(16, 0);
     lcd.print(" ");
  }

    
    lcd.setCursor(4, 0);
    lcd.print("  SEICENTO    ");
    lcd.setCursor(0, 1);
    lcd.print("DISTANZA :");
    lcd.print(distanza);
    lcd.print("cm");
    lcd.setCursor(0, 2);
    lcd.write(1);
    
       if(distanza<=150){
  lcd.setCursor(1, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(800);
  digitalWrite(Cicalino,LOW);
 }
    else {                                          
    lcd.setCursor(1, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
}

   if(distanza<=140){
  lcd.setCursor(2, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(750);
  digitalWrite(Cicalino,LOW);

 }

    else {                                          
    lcd.setCursor(2, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
}
      if(distanza<=130){
  lcd.setCursor(3, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(650);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(3, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

         if(distanza<=120){
  lcd.setCursor(4, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(600);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(4, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

         if(distanza<=110){
  lcd.setCursor(5, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(550);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(5, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

         if(distanza<=100){
  lcd.setCursor(6, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
   delay(450);
   digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(6, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

    if(distanza<=90){
  lcd.setCursor(7, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(400);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(7, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

    if(distanza<=80){
  lcd.setCursor(8, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(300);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(8, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

  if(distanza<=70){
  lcd.setCursor(9, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(200);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(9, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   } 

     if(distanza<=60){
  lcd.setCursor(10, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(150);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(10, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   }


    if(distanza<=50){
  lcd.setCursor(11, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(100);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(11, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   }

    if(distanza<=40){
  lcd.setCursor(12, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(70);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(12, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   }

    if(distanza<=30){
  lcd.setCursor(13, 2);
  lcd.write(0);
  digitalWrite(Cicalino,HIGH);
  delay(30);
  digitalWrite(Cicalino,LOW);
 }
 
    else {                                          
    lcd.setCursor(13, 2);
    lcd.print(" ");
    digitalWrite(Cicalino,LOW);
   }

       if(distanza<=20){
  lcd.setCursor(14, 2);
  lcd.write(0);
  lcd.print("STOP!");
  digitalWrite(Cicalino,HIGH);
 }
 
    else {                                          
    lcd.setCursor(14, 2);
    lcd.print("      ");
    digitalWrite(Cicalino,LOW);
   }



    lcd.setCursor(0, 3);
    lcd.print("TEMP=");
    lcd.print((float)dht.readTemperature());
    lcd.print("C ");
    lcd.print("H=");
    lcd.print((float)dht.readHumidity());
    lcd.print("%");
  }
    
     else { 
     FrecciaDestra=digitalRead(FrecciaD);
     FrecciaSinistra=digitalRead(FrecciaS);
    LuceRetronebbia=digitalRead(Retronebbia);
     LuciPosizione=digitalRead(Posizione);
     value = analogRead(Batteria);

  


     if(statobottone>=700){
digitalWrite(accensione,HIGH);
delay(800);
}

else{
 digitalWrite(accensione,LOW);
   
   vout = (value * 4.9) / 1024.0; 
   // inserire al posto di 5.0V l`uscita in volt tra i Pin 5V e GND del vostro Arduino
   
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;
} 

Serial.println(vin);
   
   if(FrecciaDestra==1){
  lcd.setCursor(18, 0);
  lcd.print("->");

 }
    else {                                          
    lcd.setCursor(18, 0);
    lcd.print("  ");
  }  



   if(FrecciaSinistra==1){
  lcd.setCursor(0, 0);
  lcd.print("<-");
 }
    else {                                          
    lcd.setCursor(0, 0);
    lcd.print("  ");
  }  

    if(LuciPosizione==1){
  lcd.setCursor(2, 0);
  lcd.write(3);
  lcd.write(2);
 }
    else {                                          
    lcd.setCursor(2, 0);
    lcd.print("  ");
  }  

     if(LuceRetronebbia==1){
  lcd.setCursor(17, 0);
  lcd.write(4);
  
 }
    else {                                          
    lcd.setCursor(17, 0);
    lcd.print("  ");
}

if(vin>=13){
  lcd.setCursor(16, 0);
  lcd.write(5);
  
 }
    else {                                          
     lcd.setCursor(16, 0);
     lcd.print(" ");
  }













    lcd.setCursor(4, 0);
    lcd.print("  SEICENTO    ");
    lcd.setCursor(0, 1);
    ("                               ");
    
  lcd.setCursor(0, 2);
  lcd.print("BAT=");
  lcd.print(vin);
  lcd.print("V                ");

    
    
    lcd.setCursor(0, 3);
    lcd.print("TEMP=");
    lcd.print((float)dht.readTemperature());
    lcd.print("C ");
    lcd.print("H=");
    lcd.print((float)dht.readHumidity());
    lcd.print("%");
       delay(250);
    }
 
    }
    }



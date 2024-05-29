const int bottone=3;
const int accensione=2;
int statobottone;



void setup() {
pinMode(bottone, INPUT);
pinMode(accensione, OUTPUT);


}

void loop() {
statobottone = digitalRead(bottone);

if(statobottone==1){
digitalWrite(accensione,HIGH);
delay(800);
}

else{
 digitalWrite(accensione,LOW); 
}

   










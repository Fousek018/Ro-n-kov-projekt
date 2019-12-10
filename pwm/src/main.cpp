#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0; 
int fan = 11; 
int led = 8; 
int temp;
int tempMin = 30; //ventilator se spustí na 30C
int tempMax = 60; //maximanlní teplota
int fanSpeed;
int fanLCD;

void setup() {
pinMode(fan, OUTPUT);
pinMode(led, OUTPUT);
pinMode(tempPin, INPUT);
lcd.begin(16,2);
Serial.begin(9600);
}

void loop()
{
temp = readTemp(); //získá teplotu
Serial.print( temp );
if(temp < tempMin) //když je teplota nížší než nejnížší teplota
{
fanSpeed = 0; // 
analogWrite(fan, fanSpeed);
fanLCD=0;
digitalWrite(fan, LOW);
}
if((temp >= tempMin) && (temp <= tempMax)) //když je teplota vyšší než nejnížší možná 
{
fanSpeed = temp;
map(temp, tempMin, tempMax, 0, 100); //přemapováni větráku
fanSpeed=1.5*fanSpeed;
fanLCD = map(temp, tempMin, tempMax, 0, 100); 
analogWrite(fan, fanSpeed); //roztočí větrák na požadovanou rychlost
}

if(temp > tempMax) //když je teplota vyšší než maximální
{
digitalWrite(led, HIGH); //zapne se ledka
}
else 
{
digitalWrite(led, LOW);//vypne se ledka
}

lcd.print("TEMP: ");
lcd.print(temp); //zobrazí se teplota na lcd display
lcd.print("C ");
lcd.setCursor(0,1); //posune kurzor na další řádek
lcd.print("FANS: ");
lcd.print(fanLCD); //zobrazí počet otáček
lcd.print("%");
delay(200);
lcd.clear();
}

int readTemp() { 
temp = analogRead(tempPin);
return temp * 0.48828125;
} 

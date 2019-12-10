#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0;

int led = 8; // led pin
int temp;
int tempMin = 30; 
int tempMax = 60; 
int fanSpeed;


int readTemp() { // get the temperature and convert it to celsius
temp = analogRead(tempPin);
return temp * 0.48828125;
}
void setup() {
pinMode(fan, OUTPUT);
pinMode(led, OUTPUT);
pinMode(tempPin, INPUT);
lcd.begin(16,2);
Serial.begin(9600);
}

void loop()
{
temp = readTemp(); // get the temperature
Serial.print( temp );



}


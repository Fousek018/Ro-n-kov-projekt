#include <Arduino.h>
int led = 12;
int tempPin = A0;
int temp;
int ledPwm= 0;
int tempMin = 300; // the temperature to start the fan 0%
int tempMax = 1000;
int i = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(led, OUTPUT);
pinMode(tempPin, INPUT);
Serial.begin(9600);
}
float readTemp(){ 
temp = analogRead (tempPin);
return temp * 0.48828125;
}
void loop() {
i++;
temp = readTemp();
Serial.print(temp);
Serial.print("\n");
delay(2000);
if(temp < tempMin)
{
ledPwm = 0; // led is of
digitalWrite(led, LOW);
}
if((temp >= tempMin) && (temp <= tempMax)) // if temperature is higher than minimum temp
{
ledPwm = 1; // led is on
digitalWrite(led, HIGH);
}
}
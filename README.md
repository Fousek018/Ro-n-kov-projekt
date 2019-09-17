# Ročníkový projekt

                                        Arduino fan temperature controler
                                      
Cílem projektu je pwm regulace větráku pomocí teploty, nebo přes bluetooth.                                     

Duležite odkazy:
https://www.electroschematics.com/9540/arduino-fan-speed-controlled-temperature/
https://www.youtube.com/watch?v=OCsmMD4wtNQ https://drive.google.com/file/d/0B7I6...
https://www.youtube.com/watch?v=R7lmpIAsoQQ
Komponenty:

Dht11- https://www.laskarduino.cz/arduino-senzor-teploty-a-vlhkosti-vzduchu-dht11/
Arduino UNO R3, ATmega328P, Klon- https://www.laskarduino.cz/arduino-uno-r3--atmega328p--klon/
Bluetooth modul HC-05 TTL- https://www.laskarduino.cz/bluetooth-modul-hc-05-ttl/
ARCTIC P12 PWM 120mm
Lcd display 16*2- https://www.gme.cz/alfanumericky-lcd-displej-16x2-zlutozeleny-hd44780


Harmonogram:
Záři- objednání komponentů
Říjen- sestavení komponentů
Listopad- vymýšlení zdrojového kodu
Prosinec- dokumentace

PWM regulace

int sensorPin = A0;
int PWM = 3;
int sensorVal;
int PWMVal;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  pinMode(PWM, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //this code prints sensor value to the console
  Serial.println(sensorVal);
  delay(1000);

  //read sensor value and set upper limit cap
  sensorVal = analogRead(sensorPin);
  if(sensorVal >800){
    sensorVal = 800;
  }

  //map and assign pwm values to the fan output 0 to 255 corresponds to 0 to 100%
  PWMVal = map(sensorVal, 450, 800, 26, 255);

  //set 450 as out cutout or cut in limit where the fan switches from off to the lower PWM limit
  if(sensorVal <450){
    PWMVal = 0;
  }

  //write the PWM value to the pwm output pin
  analogWrite(PWM, PWMVal);

}

#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0; // the output pin of LM35
int fan = 11; // the pin where fan is
int led = 8; // led pin
int temp;
int tempMin = 30; // the temperature to start the fan 0%
int tempMax = 60; // the maximum temperature when fan is at 100%
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
temp = readTemp(); // get the temperature
Serial.print( temp );
if(temp < tempMin) // if temp is lower than minimum temp
{
fanSpeed = 0; // fan is not spinning
analogWrite(fan, fanSpeed);
fanLCD=0;
digitalWrite(fan, LOW);
}
if((temp >= tempMin) && (temp <= tempMax)) // if temperature is higher than minimum temp
{
fanSpeed = temp;//map(temp, tempMin, tempMax, 0, 100); // the actual speed of fan//map(temp, tempMin, tempMax, 32, 255);
fanSpeed=1.5*fanSpeed;
fanLCD = map(temp, tempMin, tempMax, 0, 100); // speed of fan to display on LCD100
analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed
}

if(temp > tempMax) // if temp is higher than tempMax
{
digitalWrite(led, HIGH); // turn on led
}
else // else turn of led
{
digitalWrite(led, LOW);
}

lcd.print("TEMP: ");
lcd.print(temp); // display the temperature
lcd.print("C ");
lcd.setCursor(0,1); // move cursor to next line
lcd.print("FANS: ");
lcd.print(fanLCD); // display the fan speed
lcd.print("%");
delay(200);
lcd.clear();
}

int readTemp() { // get the temperature and convert it to celsius
temp = analogRead(tempPin);
return temp * 0.48828125;
}

//Example: Use of analog temperature sensor

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define beta 3950 //the beta of the thermistor
#define resistance 10 //pull up resistor value

const int digitalPin = 7; // Analog Temperature Sensor pin D0 to pin7
int analogPin = A0; // Analog Temperature Sensor pin A0 to pin A0
const int ledPin1 = 13; // red LED light
const int ledPin2 = 12; // green LED light
const int ledPin3 = 11; // blue LED light

boolean Dstate = 0; // variable for reading status of D0
int Astate = 0; // variable for reading status of A0
int buzzerPin = 8;

void setup() {
pinMode(ledPin1, OUTPUT); // initialize the LED pin as an output:
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(digitalPin, INPUT); // initialize Analog Temperature Sensor D0 pin as an input
Serial.begin(9600); // initialize serial communications at 9600 bps
  lcd.backlight();
  lcd.begin();
  lcd.setCursor(0, 0); //first column, row #1
  lcd.print("Hello World");
  delay(2000); //delay 2000ms
  lcd.clear(); //clear LCD display
  lcd.setCursor(0, 0); //first column, row #1
  lcd.print("Temperature");
  lcd.setCursor(0, 1); //second colum, row #1
  lcd.print("Sensor");
  delay(2000); //delay 2000ms
  lcd.clear(); //clear LCD display
}

void loop() {
long a = 1023 - analogRead (analogPin);
float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0)- 273.0;
int Astate = analogRead(analogPin); // read Analog Temperature Sensor A0 value (set point)
int Dstate = digitalRead(digitalPin); // read state of Analog Temperature Sensor D0
Serial.print("D0: ");
Serial.println(Dstate);//print the value of D0
Serial.print("A0:");
Serial.println(Astate);//print the value of A0, when A0 drops below 405, d0 will turn HIGH
Serial.print("Temperature:");
Serial.println(tempC);

//print values on LCD screen 
lcd.print("Temperature:");
lcd.setCursor(10, 1); //second coulumn, row#5
lcd.print(tempC); //print temperature 
lcd.setCursor(15, 1); //second coulumn, row#8
lcd.print("C");  //unit of temperature

//setup ranges of the buzzer and LEDs 
if ((tempC > 20) && (tempC <=26))   { 
    delay(1000); //delay 1000ms
    digitalWrite (ledPin3, HIGH);
    digitalWrite (ledPin2, LOW);
    digitalWrite (ledPin1, LOW);
    tone(buzzerPin, 300,100); }   
if ((tempC > 26) && (tempC <=33))   { 
    delay(500); //delay 500ms
    digitalWrite (ledPin3, LOW);
    digitalWrite (ledPin2, HIGH);
    digitalWrite (ledPin1, LOW);
    tone(buzzerPin, 500,100); }
if (tempC > 33)   { 
    delay(100); //delay 100ms
    digitalWrite (ledPin3, LOW);
    digitalWrite (ledPin2, LOW);
    digitalWrite (ledPin1, HIGH);
    tone(buzzerPin, 1000,100);}
if (tempC <=20)   { 
    delay(1000); //delay 1000ms
    digitalWrite (ledPin3, LOW);
    digitalWrite (ledPin2, LOW);
    digitalWrite (ledPin1, LOW);
    noTone(buzzerPin);    }}

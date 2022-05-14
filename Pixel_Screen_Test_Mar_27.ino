//www.diyusthad.com
#include <LiquidCrystal.h>
#define contra 10
#define bri 27
//#define bri 27 // does wierd things


int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor


int n = 0;
int test = 0;

int hours1 = 0;
int hours2 = 0;

int minutes1 = 0;
int minutes2 = 0;

int seconds1 = 0;
int seconds2 = 0;


const int rs = 12, en = 11, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  
  lcd.begin(16, 2);

  
  pinMode(contra, OUTPUT);
  pinMode(bri, OUTPUT);
  
  //digitalWrite(contra, LOW); //outputs no power to the contrast pin. this lets you see the words
  
  analogWrite(bri, 255);
  analogWrite(contra, 100);
  

//  lcd.noCursor();
//  lcd.noBlink();
//  lcd.noAutoscroll();
  
//  Tets for LCD
//  lcd.print("Hello World!");
//  lcd.setCursor(0,1);
//  lcd.print("");
//
  lcd.setCursor(0,0);
  lcd.print("Time");
  lcd.setCursor(0,1);


  Serial.begin (9600);
}


void loop() {

  lcd.noCursor();
  lcd.noBlink();
  lcd.noAutoscroll();

  sensorValue = analogRead(sensorPin);
  n = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(contra, n);
  Serial.println(n);


//  lcd.setCursor(0,1);
//  lcd.print("-");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("\\");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("|");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("/");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("-");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("\\");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("|");
//  delay(1000);
//  lcd.setCursor(0,1);
//  lcd.print("/");
//  delay(1000);
//  test++;

  
  lcd.clear();
}

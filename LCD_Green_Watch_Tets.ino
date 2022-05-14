
// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD


// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.


int sensorPin = A0; // select the input pin for LDR 
int sensorValue = 0; // variable to store the value coming from the sensor


//PSB - Pause Start Button, its purpose to stop and start the clock
const int PSB = 3;
//AddB - Add Button, its purpose to add time 
const int AddB = 5;
//MoveB - Move Button, its purpose to decide wher eto add time
const int MoveB = 6;

//PS, 1 = Start, -1 = Pause
int PS = 1;
//PosB, posotion of addign time, hours = 3600, minutes = 60, or seconds = 1
int PosB = 1;

// Position and direction of | for loading 1 screen
int x = 0;
int y = 1;

// Initiate buttons state
int buttonState1;
int buttonState2;
int buttonState3;

// Time in seconds
long seconds = 45840;


void setup() {

  Serial.begin(9600);
  
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  // Initiate buttons
  pinMode(PSB, INPUT);
  pinMode(AddB, INPUT);
  pinMode(MoveB, INPUT);
  
}


void loop() {

  // Print time
  Watch(seconds);

  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.print("Light V. :");
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen

//  // Initiate buttons state
//  int buttonState1;
//  int buttonState2;
//  int buttonState3;

  // Reade buttons state
  buttonState1 = digitalRead(PSB);
  buttonState2 = digitalRead(AddB);
  buttonState3 = digitalRead(MoveB);

  // If pressed pause or start the clock
  if(buttonState1 == LOW)
  {
    PSscreen();
  }

  // if PS is equal to start = 1 continue adding 1 second per second.
  if(PS == 1)
  {
    delay(1000);
    lcd.clear();
    seconds++; 
  }
  else if(buttonState2 == LOW) {
    seconds += PosB;
    delay(100);
  }
  else if(buttonState3 == LOW) {
    PosB *= 60;
    if(PosB > 3600) {
      PosB = 1;
      SecondsMode();
    }
    else if(PosB == 60) {
      MinutesMode();
    }
    else {
      HoursMode();
    }
    lcd.clear();
  }

  // Check if time is equal or more than 24 hours
  if(seconds >= 86400) {
    seconds = 0;
  }
  
}


void Loading1() {
  lcd.setCursor(0,0);
  lcd.print("Loading");
  lcd.setCursor(0,1);
  lcd.print("-");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("\/");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("|");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("/");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("-");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("\/");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("|");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("/");
  delay(100);
}


void Loading2() {
  if(x == 16)
  {
    y = -1;
    x = 14;
  }
  else if(x == -1)
  {
    y = 1;
    x = 1;
  }
  
  lcd.setCursor(x, 0);
  lcd.print("|");
  lcd.setCursor(x, 1);
  lcd.print("|");

  x += y;

  delay(100);
  lcd.clear();
}


void Loading3() {
  lcd.setCursor(0,0);
  lcd.print("Loading ");
  lcd.setCursor(0,1);
  lcd.print("Pls Wait");
  lcd.setCursor(12,0);
  lcd.print("#");
  delay(100); 
  lcd.setCursor(13,0);
  lcd.print("#");
  delay(100);
  lcd.setCursor(13,1);
  lcd.print("#");
  delay(100);
  lcd.setCursor(12,1);
  lcd.print("#");
  delay(100);
  lcd.setCursor(12,0);
  lcd.print(" ");
  delay(100); 
  lcd.setCursor(13,0);
  lcd.print(" ");
  delay(100);
  lcd.setCursor(13,1);
  lcd.print(" ");
  delay(100);
  lcd.setCursor(12,1);
  lcd.print(" ");
  delay(100); 
}


void Watch(long seconds) {
  lcd.setCursor(0,0);
  lcd.print("Time");

  Serial.print("initial: ");
  Serial.println(seconds);
  
  int hours = (seconds - seconds % 3600) / 3600;
  seconds = seconds % 3600;
  int minutes = (seconds - seconds % 60) / 60;
  seconds = seconds % 60;

  Serial.print("hours: ");
  Serial.println(hours);
  Serial.print("minutes: ");
  Serial.println(minutes);
  Serial.print("seconds: ");
  Serial.println(seconds);
  
  Serial.println();
  Serial.println();
  
  if(hours < 10) {
    lcd.setCursor(0,1);
    lcd.print("0");
    lcd.setCursor(1,1);
    lcd.print(hours);
    lcd.print(":");
  }
  else {
    lcd.setCursor(0,1);
    lcd.print(hours);
    lcd.print(":");
  }

  if(minutes < 10) {
    lcd.setCursor(3,1);
    lcd.print("0");
    lcd.setCursor(4,1);
    lcd.print(minutes);
    lcd.print(":");
  }
  else {
    lcd.setCursor(3,1);
    lcd.print(minutes);
    lcd.print(":");
  }

  if(seconds < 10) {
    lcd.setCursor(6,1);
    lcd.print("0");
    lcd.setCursor(7,1);
    lcd.print(seconds);
  }
  else {
    lcd.setCursor(6,1);
    lcd.print(seconds);
  }
}


void PSscreen() {
  PS *= -1;
  lcd.clear();
  int n = 0;
  
  while(n < 2)
  {
    Loading3();
    n++;  
  }
  lcd.clear();
  
  Serial.println(PS);
  delay(100);
}


void SecondsMode() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mode: Seconds");
  delay(500);
}


void MinutesMode() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mode: Minutes");
  delay(500);
}


void HoursMode() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mode: Hours");
  delay(500);
}


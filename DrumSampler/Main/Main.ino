#include "defines.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

int x, y;
byte sw;

// Joystick joystick;
int js;

void setup() {
  // Wire.begin();

  Serial.begin(9600);
  while (!Serial) {delay(10);}

  /*
    if (!display.begin()) {
      Serial.print("Did not find device at 0x");
      Serial.println(display.address(), HEX);
  }
  */
  lcd.init();
  lcd.init();
  lcd.backlight();
  Serial.println("Display initialized.");
  
  // init joystick
  pinMode(JOYSTICK_SW, INPUT);
  digitalWrite(JOYSTICK_SW, HIGH);

  Serial.println("Joystick initialized.");
  
}
void loop() {
 

  updateJoystick();
  updateDisplay(js++);

  delay(200);

}
void updateDisplay(int val) {
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print(val);
}

void updateJoystick() {
  x = analogRead(JOYSTICK_X);
  y = analogRead(JOYSTICK_Y);
  sw = digitalRead(JOYSTICK_SW);
   /*
  printScalars(x, y, sw);
  */
  printDirections(x, y, sw);
}

void printDirections(int x, int y, byte sw) {

  if (isCentered(x)) {
    Serial.print("x-center  ");
  } else {
    Serial.print((x < 400) ? "left " : "");
    Serial.print((x > 700) ? "right " : "");
    // Serial.print(x);
    // Serial.print(" ");
  }

  if (isCentered(y)) {
    Serial.print(" y-center ");
  } else {
    Serial.print((y < 400) ? "down " : "");
    Serial.print((y > 700) ? "up" : "");
    // Serial.print(y);
    // Serial.print(" ");
  }

  if (sw == 1) {
    Serial.print(" not");
  }

  Serial.println(" clicked");
}

void printScalars(int x, int y, byte sw) {
  Serial.print (x);
  Serial.print (" ");

  Serial.print (y);
  Serial.print (" ");
  Serial.println(sw);
}


bool isCentered(int value) {
  return ((value > 399) && (value < 700));
}

bool goesLeft(int value) {
  return (value < 400);
}

bool goesRight(int value) {
  return (value > 700);
}

bool goesUp(int value) {
  return (value > 700);
}

bool goesDown(int value) {
  return (value < 400);
}

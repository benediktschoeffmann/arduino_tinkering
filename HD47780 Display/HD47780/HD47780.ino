/*
 * This sketch exists because I want to know, how 
 * the stuff with the LCDs works. 
 * 
 * Also _some_ visual hints when debugging would be nice D:
 */

#include <LiquidCrystal.h>

#ifndef HD47780_INO
#define HD47780_INO

#define PIN_LCD_RS 12             // Register Select
#define PIN_LCD_EN  11            // Enable
#define PIN_LCD_D4 5              // Bit 4
#define PIN_LCD_D5 4              // Bit 5
#define PIN_LCD_D6 3              // Bit 6
#define PIN_LCD_D7 2              // Bit 7

#define LCD_ROWS 2                // Rows
#define LCD_COLS 16               // Columns


LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
byte i = 0, y = 0, x = 0;

void setup() {
  lcd.begin(LCD_COLS, LCD_ROWS);  
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  i = i % 32;

  y = (i < 16) ? 0 : 1;
  x = abs((-y*16) + i % 16);
  lcd.setCursor(x, y);
  lcd.write('*');
  delay(100);
  lcd.setCursor(x, y);
  lcd.write(' ');
  i++;
}

#endif

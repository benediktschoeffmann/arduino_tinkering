/*
 * Prototype for a Arduino based Sequencer .... WIP
 */

#include <LiquidCrystal.h>

#ifndef SEQ_INO
#define SEQ_INO



/* -----------------DEFINE PINS--------------*/
#define PIN_LCD_RS 12             // Register Select
#define PIN_LCD_EN  11            // Enable
#define PIN_LCD_D4 5              // Bit 4
#define PIN_LCD_D5 4              // Bit 5
#define PIN_LCD_D6 3              // Bit 6
#define PIN_LCD_D7 2              // Bit 7

#define PIN_BPM A0                // AnalogIn0 = BPM
#define BPM_MIN 80
#define BPM_MAX 220

#define PIN_CV A1                 // AnalogIn1 = Control Voltage from Sequencer

#define PIN_OCT A2                // AnalogIn2 = Octave
#define OCT_MIN -2
#define OCT_MAX 2

#define PIN_CLOCK 6              // Clock

/* -----------------LCD-------------------------*/
#define LCD_ROWS 2                // Rows
#define LCD_COLS 16               // Columns

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
/* ----------------------------------------------*/

byte bpm;
int octave, tick, cv;

void setup() {
  lcd.begin(LCD_COLS, LCD_ROWS);  
  lcd.clear();
  Serial.begin(9600);
  pinMode(PIN_BPM, INPUT);
  pinMode(PIN_CV, INPUT);
  pinMode(PIN_CLOCK, OUTPUT);
}

void updateDisplay() {
  lcd.clear();
  // BPM
  lcd.setCursor(12,1);
  lcd.print('B');
  lcd.print(bpm);
  // Octave
  lcd.setCursor(9,1);
  lcd.print('O');
  lcd.print(octave);
  // CV
  lcd.setCursor(1,1);
  lcd.print("CV");
  lcd.print(cv);
}

byte getBPM() {
  int b  = analogRead(PIN_BPM);
  return map(b, 10, 1009, BPM_MIN, BPM_MAX);
}

int getOctave() {
  int o = analogRead(PIN_OCT);
  return map(o, 10, 1009, OCT_MIN, OCT_MAX);
}

int getTick(int bpm) {
  return 60000/(bpm*2);
}

void loop() {
  bpm = getBPM();
  octave = getOctave();
  tick = getTick(bpm);
  cv = analogRead(PIN_CV);
  updateDisplay();

  Serial.println(tick);
  
  digitalWrite(PIN_CLOCK, HIGH);
  delay(tick);
  digitalWrite(PIN_CLOCK, LOW);
  delay(tick);
}

#endif

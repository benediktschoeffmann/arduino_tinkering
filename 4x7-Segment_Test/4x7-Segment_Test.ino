#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK   5
#define DIO   6
#define TEMPO A0

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000
#define BPM_MIN    66.0f
#define BPM_MAX   240.0f

TM1637Display display(CLK, DIO);

double bpm, last;
double delta = 1;
int k;

void setup()
{
  pinMode(TEMPO, INPUT);
  display.setBrightness(0x08);
  Serial.begin(57600);
  Serial.println("init done. ");
}

double readBpm() {
  k = analogRead(TEMPO);
  k = map(k, 0.0f, 1024.0f, BPM_MIN, BPM_MAX);
  if (abs(k - last) > delta) {
    bpm = k;
  }

  last = k;
  return bpm;
}

void loop()
{
  bpm = readBpm();
  Serial.println(bpm);
  delay(100);

  display.showNumberDec(bpm, false, 4, 0);
  delay(400);
}

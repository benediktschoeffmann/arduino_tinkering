#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_ST7735.h>
#include "RotaryEncoder.h"
#include "Pins.h"

const short MAX_STEPS = 64;

RotaryEncoder rotaryEncoder = RotaryEncoder(ENCODER_PIN_CLK, ENCODER_PIN_DT, ENCODER_PIN_SW);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int uiStep = 0;

void setup() {
  Serial.begin(57600);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
}

void loop() {
  checkEncoder();
}

void checkEncoder() {
  unsigned char result = rotaryEncoder.process();
  if (result == DIR_CW) {
    uiStep = changeUiStep(true);
    Serial.println(uiStep);
    
  } else if (result == DIR_CCW) {
    uiStep = changeUiStep(false);
    Serial.println(uiStep);
    
  }
  if (result & DIR_SW) {
    Serial.println("button");
  }
}

int changeUiStep(bool increment) {
  if (increment) {
    uiStep++;
    if (uiStep >= MAX_STEPS) {
      uiStep = 0;
    }
  } else {
    uiStep--;
    if (uiStep < 0) {
      uiStep = MAX_STEPS-1;
    }
  }

  return uiStep;
}

int getTickInMilliseconds(int bpm) {
  return (60000/(bpm*4));
}

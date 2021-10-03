#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "RotaryEncoder.h"
#include "Pins.h"

const byte MAX_UI_STEPS           = 64;
const byte MAX_PATTERN_STEPS      = 16;

const unsigned short SCREEN_WIDTH           = 160;
const unsigned short SCREEN_HEIGHT          = 128;

const unsigned short TEMPO_DEBOUNCE_MARGIN  = 10;
const unsigned short TEMPO_DEBOUNCE_DELAY   = 200;

const unsigned short TEMPO_MIN              = 80;
const unsigned short TEMPO_MAX              = 222;


const unsigned short xGridPositions[] = { 32, 48, 64, 80, 96, 112, 128, 144, 160, 176 };
const unsigned short yGridPositions[] = { 3, 16, 28, 41, 53, 66, 78, 91, 103 }; 

RotaryEncoder rotaryEncoder = RotaryEncoder(ENCODER_PIN_CLK, ENCODER_PIN_DT, ENCODER_PIN_SW);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

short uiStep = 0, lastUiStep = 0;
bool encoderWasClicked = false;

short tempoValue, oldTempoValue;
short bpm = 100;
short ticks = 150;
long tempoLastChange = millis();

byte textMarginVert = 32;
byte textLineHeight = 25;
byte menuMarginVert = 55;
byte ymin = 3;
byte deltaX = 16;

byte steps[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte mask;

void setup() {
  initDisplay();
  
  pinMode(TEMPO, INPUT);
  oldTempoValue = analogRead(TEMPO);
  tempoValue = oldTempoValue;
  
  Serial.begin(57600);
  Serial.println("Start");

  drawMenu(ST7735_YELLOW);
  drawGrid(ST7735_WHITE);
  drawUiStep(uiStep, ST7735_RED);
}

void loop() {
  if (checkEncoder()) {
    Serial.print(lastUiStep);
    Serial.print("\t");
    Serial.print(uiStep);
    Serial.print("\t");
    if (checkEncoderClick()) {
      byte mask = 1 << (uiStep >> 4);      
      steps[uiStep >> 4] ^= mask;
    }
    Serial.println();
    
    drawUiStep(uiStep, ST7735_RED);
    drawUiStep(lastUiStep, ST7735_BLACK);
    drawNotes(0xD69A);
    drawGrid(ST7735_WHITE);
  } 

  if (checkForTempoChange()) {
    Serial.print("New Tempo: ");
    Serial.println(bpm);
  }
}

void initDisplay() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setRotation(1);
}

void drawMenu(uint16_t lineColor) {
  tft.drawRect(0, 0, SCREEN_WIDTH, ymin, lineColor);
  
  tft.drawLine(0, ymin + textLineHeight, textMarginVert, ymin + textLineHeight, lineColor);
  tft.drawLine(0, ymin + 2*textLineHeight, textMarginVert, ymin + 2*textLineHeight, lineColor);
  tft.drawLine(0, ymin + 3*textLineHeight, textMarginVert, ymin + 3*textLineHeight, lineColor);
  tft.drawLine(0, ymin + 4*textLineHeight, SCREEN_WIDTH, ymin + 4*textLineHeight, lineColor);

  tft.drawLine(textMarginVert, ymin + 0, textMarginVert, ymin + 4*textLineHeight, lineColor);

  tft.drawLine(menuMarginVert,  ymin + 4*textLineHeight, menuMarginVert, SCREEN_HEIGHT, lineColor);
  tft.drawLine(2*menuMarginVert,  ymin + 4*textLineHeight, 2*menuMarginVert, SCREEN_HEIGHT, lineColor);
}

void drawGrid(uint16_t lineColor) {
  for (byte j = 0; j < 8; j++) {
    tft.drawLine(xGridPositions[j], ymin, xGridPositions[j], ymin+4*textLineHeight, lineColor);      
  }

  for (byte i = 8; i > 0; i--) {
    tft.drawLine(textMarginVert, yGridPositions[i], SCREEN_WIDTH, yGridPositions[i], lineColor);
  }
}

void drawUiStep(byte currentStep, uint16_t rectColor) {
  tft.fillRect(xGridPositions[currentStep & 0x7] + 1, yGridPositions[(currentStep) / 8] + 1, deltaX-1, 12, rectColor);
}

void drawNotes(uint16_t color) {
  for (byte i = 0; i < 16; i++) {
    if (steps[i] & 1) {
      drawUiStep(i, color);      
    }

    if (steps[i] & 2) {
      drawUiStep(16+i, color);      
    }

    if (steps[i] & 4) {
      drawUiStep(32+i, color);      
    }

    if (steps[i] & 8) {
      drawUiStep(64+i, color);      
    }
    
  }
}



bool checkForTempoChange() {
  tempoValue = analogRead(TEMPO);
  if (abs(tempoValue - oldTempoValue) > TEMPO_DEBOUNCE_MARGIN) {
    if ((millis() - tempoLastChange) > TEMPO_DEBOUNCE_DELAY){
        oldTempoValue = tempoValue;
        bpm = map(tempoValue, 0, 1024, TEMPO_MIN, TEMPO_MAX);
        ticks = getTicksInMilliseconds(bpm);
        tempoLastChange = millis();
        return true;
    }
  }

  return false;
}

bool checkEncoderClick() {
  if (encoderWasClicked) {
    encoderWasClicked = false;
    return true;
  }

  return false;
}

bool checkEncoder() {
  unsigned char result = rotaryEncoder.process();
  if (result == DIR_CW) {
    uiStep = changeUiStep(true);
    // Serial.println(uiStep);
    return true;
  } else if (result == DIR_CCW) {
    uiStep = changeUiStep(false);
    // Serial.println(uiStep);
    return true;
  }
  if (result & DIR_SW) {
    encoderWasClicked = true;
    return true;
  }

  return false;
}

int changeUiStep(bool increment) {

  lastUiStep = uiStep;

  if (increment) {
    uiStep++;
    if (uiStep >= MAX_UI_STEPS) {
      uiStep = 0;
    }
  } else {
    uiStep--;
    if (uiStep < 0) {
      uiStep = MAX_UI_STEPS - 1;
    }
  }

  return uiStep;
}

int getTicksInMilliseconds(uint8_t bpm) {
  return (60000 / (bpm * 4));
}

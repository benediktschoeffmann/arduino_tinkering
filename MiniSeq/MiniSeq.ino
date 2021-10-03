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

const unsigned short BUTTON_DEBOUNCE_DELAY   = 200;

const unsigned int COLOR_PLAYER_POSITION_NOW = 0x021D;
const unsigned int COLOR_PLAYER_POSITION_LAST = 0x74BD;
const unsigned int COLOR_PATTERN_POSITION_SET = 0xD69A;



const unsigned short xGridPositions[] = { 32, 48, 64, 80, 96, 112, 128, 144, 160, 176 };
const unsigned short yGridPositions[] = { 3, 16, 28, 41, 53, 66, 78, 91, 103 }; 
const unsigned short xPlayPositions[] = { 60, 66, 71, 77, 82, 88, 93, 99 };
const unsigned short yPlayPositions[] = { 113, 118 };

char* channelNames[] = {"CH1", "CH2", "CH3", "CH4"};

RotaryEncoder rotaryEncoder = RotaryEncoder(ENCODER_PIN_CLK, ENCODER_PIN_DT, ENCODER_PIN_SW);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

short uiStep = 0, lastUiStep = 0;
short playerStep = 0;
bool encoderWasClicked = false;

short tempoValue, oldTempoValue;
short bpm = 100;
short ticks = 150;

long updateLastChange;
long tempoLastChange = millis();
long buttonLastChange = millis();

byte textMarginVert = 32;
byte textLineHeight = 25;
byte menuMarginVert = 55;
byte ymin = 3;
byte deltaX = 16;

short steps[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
short patternData;
short mask;

boolean isRunning = false;

void setup() {
  initDisplay();
  
  pinMode(TEMPO, INPUT);
  oldTempoValue = analogRead(TEMPO);
  tempoValue = oldTempoValue;

  pinMode(START_PIN, INPUT_PULLUP);
  
  Serial.begin(57600);
  Serial.println("Start");

  drawMenu(ST7735_YELLOW);
  drawGrid(ST7735_WHITE);
  drawUiStep(uiStep, ST7735_RED);
  drawChannelNames(ST7735_YELLOW, 1);
  drawBPM(ST7735_YELLOW, 1);
  drawPlayerState(isRunning);
  
}

void loop() {

  if (isRunning) {
    if ((millis() - updateLastChange) >= ticks) {
      updateLastChange = millis();
      playerStep = (playerStep+1) & 0xf;
      drawPlayerStep(playerStep, false);
      drawPlayerStep((playerStep-1) & 0xf, true);
      tft.fillRect(xPlayPositions[(playerStep-2) & 0x7], yPlayPositions[(((playerStep-2) & 0xf) >> 3) & 0x1], 4, 4, ST7735_BLACK);

      if ((patternData = checkPatternData(playerStep)) != 0) {
        outputAudio(patternData);
      }
    }
  }

  if (checkEncoder()) {
    Serial.print(lastUiStep);
    Serial.print("\t");
    Serial.print(uiStep);
    Serial.print("\t");
    Serial.println();
    if (checkEncoderClick()) {
      byte mask = 1 << (uiStep >> 4);      
      steps[uiStep & 0xf] ^= mask;
      /*
      Serial.print("Click: ");
      Serial.print("\t");
      Serial.print(uiStep);
      Serial.print("\t");
      Serial.print(uiStep >> 4);
      Serial.print("\t");
      Serial.print(1 << (uiStep >> 4));
      Serial.print("\t");
      Serial.print(steps[uiStep & 0xf]);
      Serial.println();
      */
    }
    
    drawUiStep(uiStep, ST7735_RED);
    drawUiStep(lastUiStep, ST7735_BLACK);
    drawNotes(COLOR_PATTERN_POSITION_SET);
    drawGrid(ST7735_WHITE);
  } 

  if (checkForTempoChange()) {
    drawBPM(ST7735_YELLOW, 1);
    ticks = getTicksInMilliseconds(bpm);
  }

  if (checkStartStopChange()) {
    Serial.println("Start/Stop");
    isRunning = !(isRunning);
    drawPlayerState(isRunning);

    if (isRunning) {
      updateLastChange = millis();
    }
  }
}

void outputAudio(short patternData) {
  Serial.print("\t");
  Serial.print(playerStep+1);
  Serial.print("/16: ");
    for (int i=0; i<4; i++) {
      if (patternData & (1 << i)) {
        Serial.print("CH");
        Serial.print(i+1);        
      }
      Serial.print("\t");
    }
    Serial.println();
}

short checkPatternData(short currentStep) {
  return steps[currentStep];
}
  
void initDisplay() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setRotation(1);
}

void drawMenu(uint16_t lineColor) {
  // the bar at the top
  tft.fillRect(0, 0, SCREEN_WIDTH, ymin, lineColor);

  // the four lower lines under the channelnames
  tft.drawLine(0, ymin + textLineHeight, textMarginVert, ymin + textLineHeight, lineColor);
  tft.drawLine(0, ymin + 2*textLineHeight, textMarginVert, ymin + 2*textLineHeight, lineColor);
  tft.drawLine(0, ymin + 3*textLineHeight, textMarginVert, ymin + 3*textLineHeight, lineColor);
  tft.drawLine(0, ymin + 4*textLineHeight, SCREEN_WIDTH, ymin + 4*textLineHeight, lineColor);

  // right vertical line after channelnames
  tft.drawLine(textMarginVert, ymin, textMarginVert, ymin + 4*textLineHeight, lineColor);

  // the 2 vertical lines at the bottom
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

void drawPlayerStep(short currentStep, bool isLast) {
  
   uint16_t color = (isLast) ? COLOR_PLAYER_POSITION_LAST : COLOR_PLAYER_POSITION_NOW;

  tft.fillRect(xPlayPositions[currentStep & 0x7], yPlayPositions[(currentStep >> 3) & 0x1], 5, 5, color);
  if (isLast) {
    tft.drawRect(xPlayPositions[currentStep & 0x7], yPlayPositions[(currentStep >> 3) & 0x1], 5, 5, ST7735_BLACK);
  }
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

void drawChannelNames(uint16_t color, uint8_t textSize) {
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  for (int i=0; i < 4; i++) {
    tft.setCursor(5, ymin + 10 + (i * textLineHeight));
    tft.print(channelNames[i]);
  }
}

void drawPlayerState(bool isRunning) {
  // delete background
  tft.fillRect(130, 108, 25, 20, ST7735_BLACK);
  
  if (isRunning) {
    // draw green play button
    tft.fillTriangle(
      130, 108,
      130, 128,
      150, 118,
      ST7735_GREEN
    );
  } else {
    tft.fillRect(
      130, 108,
      20, 20,
      ST7735_RED
    );
  }
}

void drawBPM(uint16_t color, uint8_t textSize) {

  tft.fillRect(5,115, 50, 20, ST7735_BLACK);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setCursor(5, 115);
  tft.print("BPM: ");
  tft.print(bpm);
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

bool checkStartStopChange() {
  int state = digitalRead(START_PIN);
  if ((digitalRead(START_PIN) == LOW) && ((millis() - buttonLastChange) > BUTTON_DEBOUNCE_DELAY)) {
    buttonLastChange = millis();
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

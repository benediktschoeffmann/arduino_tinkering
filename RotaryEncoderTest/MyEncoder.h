/*
 * Encoder encoder library for Arduino.
 */

#ifndef myencoder_h
#define myencoder_h

#include "Arduino.h"

// Enable this to emit codes twice per step.
//#define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

#define DIR_SW 0x40
#define ENCODER_DEBOUNCE_DELAY 200

class MyEncoder
{
  public:
    MyEncoder(char, char, char);
    // Process pin(s)
    unsigned char process();
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
    unsigned char pin3;
    unsigned long lastClick;
};

#endif
 

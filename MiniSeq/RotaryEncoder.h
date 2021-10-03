/*
 * Rotary encoder library for Arduino.
 */

#ifndef rotaryEncoder_h
#define rotaryEncoder_h

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
#define  DIR_CCW 0x20

#define DIR_SW 0x40
#define DEBOUNCE_DELAY 400


class RotaryEncoder
{
  public:
    RotaryEncoder(char, char, char);
    // Process pin(s)
    unsigned char process();
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
    unsigned char pin3;
    unsigned long lastEncoderClick;
};

#endif
 

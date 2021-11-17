#ifndef _PITCHES_H_
#define _PITCHES_H_

#define NOTE_B0  31.f
#define NOTE_C1  33.f
#define NOTE_CS1 35.f
#define NOTE_D1  37.f
#define NOTE_DS1 39.f
#define NOTE_E1  41.f
#define NOTE_F1  44.f
#define NOTE_FS1 46.f
#define NOTE_G1  49.f
#define NOTE_GS1 52.f
#define NOTE_A1  55.f
#define NOTE_AS1 58.f
#define NOTE_B1  62.f
#define NOTE_C2  65.f
#define NOTE_CS2 69.f
#define NOTE_D2  73.f
#define NOTE_DS2 78.f
#define NOTE_E2  82.f
#define NOTE_F2  87.f
#define NOTE_FS2 93.f
#define NOTE_G2  98.f
#define NOTE_GS2 104.f
#define NOTE_A2  110.f
#define NOTE_AS2 117.f
#define NOTE_B2  123.f
#define NOTE_C3  131.f
#define NOTE_CS3 139.f
#define NOTE_D3  147.f
#define NOTE_DS3 156.f
#define NOTE_E3  165.f
#define NOTE_F3  175.f
#define NOTE_FS3 185.f
#define NOTE_G3  196.f
#define NOTE_GS3 208.f
#define NOTE_A3  220.f
#define NOTE_AS3 233.f
#define NOTE_B3  247.f
#define NOTE_C4  262.f
#define NOTE_CS4 277.f
#define NOTE_D4  294.f
#define NOTE_DS4 311.f
#define NOTE_E4  330.f
#define NOTE_F4  349.f
#define NOTE_FS4 370.f
#define NOTE_G4  392.f
#define NOTE_GS4 415.f
#define NOTE_A4  440.f
#define NOTE_AS4 466.f
#define NOTE_B4  494.f
#define NOTE_C5  523.f
#define NOTE_CS5 554.f
#define NOTE_D5  587.f
#define NOTE_DS5 622.f
#define NOTE_E5  659.f
#define NOTE_F5  698.f
#define NOTE_FS5 740.f
#define NOTE_G5  784.f
#define NOTE_GS5 831.f
#define NOTE_A5  880.f
#define NOTE_AS5 932.f
#define NOTE_B5  988.f
#define NOTE_C6  1047.f
#define NOTE_CS6 1109.f
#define NOTE_D6  1175.f
#define NOTE_DS6 1245.f
#define NOTE_E6  1319.f
#define NOTE_F6  1397.f
#define NOTE_FS6 1480.f
#define NOTE_G6  1568.f
#define NOTE_GS6 1661.f
#define NOTE_A6  1760.f
#define NOTE_AS6 1865.f
#define NOTE_B6  1976.f
#define NOTE_C7  2093.f
#define NOTE_CS7 2217.f
#define NOTE_D7  2349.f
#define NOTE_DS7 2489.f
#define NOTE_E7  2637.f
#define NOTE_F7  2794.f
#define NOTE_FS7 2960.f
#define NOTE_G7  3136.f
#define NOTE_GS7 3322.f
#define NOTE_A7  3520.f
#define NOTE_AS7 3729.f
#define NOTE_B7  3951.f
#define NOTE_C8  4186.f
#define NOTE_CS8 4435.f
#define NOTE_D8  4699.f
#define NOTE_DS8 4978.f

int PITCHES[7][13] = {
  {NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_C2}, 
  {NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3}, 
  {NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4}, 
  {NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5}, 
  {NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6}, 
  {NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6, NOTE_C7}, 
  {NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, NOTE_C8}
};

const int KEYS[13] = {710, 632, 600, 570, 565, 557, 554, 548, 550, 546, 543, 537, 522};

#endif


# Arduino Test Sketches

Hi there, I just wanted to brush up my skills in C and Srduino tinkering.
I'll try to summarize each of these sketches a bit.

- 128x32 I2C Display
  
  Test Script for this display.

- 4x7-Segment_Test

  Test Script for this display.

- HD47780 Display

  Test Script for this display.

- ST7735S Display

  Test Script for this display.

- Blinkenlights:

  PINS 4,5,6 are S(elect)0, S1, S2 (in that order!) of a CD4051, which in turn triggers the LEDS.
  
  - Blinkenlights2:

  Arduino only sends a CLOCK signal now, to a CD4024 which is a 7-stage binary ripple-carry adder that in turn sends the Selects for the 4051.

- HD74450 (a.k.a. Blinkenlights3 :D)

  My first experience with a Display of some sort. Uses the same wiring as the official examples from the Lib.

- encoderTest

  Test Sketch using a KDY-040 Encoder. Connect CLK, DT, SW to Pins 2,3,4 , respectively.

- scales
  Just a reprensation of intervales between notes in the modes - or "church" scales.

- Hagiwo

  In this folder are various ino-files from [Hagiwo on Youtube](https://www.youtube.com/channel/UCxErrnnVNEAAXPZvQFwobQw)

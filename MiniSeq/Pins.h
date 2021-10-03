#ifndef pins_h
#define pins_h

  /* Pins for Rotary Encoder */
  #define ENCODER_PIN_CLK 2 // Rotary Encoder Clock
  #define ENCODER_PIN_DT  3 // Rotary Encoder Duty
  #define ENCODER_PIN_SW  4 // Rotary Encoder Button

  /* Start / Stop Button */
  #define START_PIN       6

  /* Pins for ST7735 */
  #define TFT_CS         10
  #define TFT_RST         9
  #define TFT_DC          8

  /* If you want to redefine these, fine, but if you use the standard-hardware-pins,
   * the graphics will be a lot faster :) 
   * #define TFT_MOSI        11
   * #define TFT_SCLK        13 
   */

  /* Pin for manual clock */
  #define TEMPO          A0

  /* Pins for thonkiconns */
  #define CH_0           A1
  #define CH_1           A2
  #define CH_2           A3
  #define CH_3           A4
  
#endif

/*
AD9833 Waveform Module vwlowen.co.uk
*/

#include <SPI.h>

const int SINE = 0x2000;                    // Define AD9833's waveform register value.
const int SQUARE = 0x2028;                  // When we update the frequency, we need to
const int TRIANGLE = 0x2002;                // define the waveform when we end writing.    
const float refFreq = 25000000.0;           // On-board crystal reference frequency
const int FSYNC = 10;                       // Standard SPI pins for the AD9833 waveform generator.


//waveform initial setting
int FormSW_A = 0;                         
int FormSW_B = 0;
int Waveform = SINE;
int old_Waveform=1;

//freq range initial setting
//AB=10->Low, =01->Mid, =00->High
int RangeA = 1;
int RangeB = 0;
long freqRange = 2000;
long old_freqRange = 0;

//VR freq initial setting
long frequency = 1;
long old_frequency = 10;

int waveType = TRIANGLE;
unsigned long freq = 2000;               // Set initial frequency.

void setup() { 

//pinmode setting
 pinMode(9,INPUT);
 pinMode(8,INPUT);
 pinMode(6,INPUT);
 pinMode(7,INPUT); 

//AD9833 reset
 Serial.begin(9600);
 Serial.println("AD9833 Test");

  
 // Can't set SPI MODE here because the display and the AD9833 use different MODES.
 SPI.begin();
 delay(50); 
  
 AD9833reset();                                   // Reset AD9833 module after power-up.
 delay(50);
 AD9833setFrequency(freq, TRIANGLE);                  // Set the frequency and Sine Wave output
   WriteRegister(0x2100);   
}


void loop() {

//waveform setting

//read waveform switch
 FormSW_A = digitalRead(8); //read waveform switch
 FormSW_B = digitalRead(9); //read waveform switch
 
//set waveform

old_Waveform = Waveform;

  if (FormSW_A == 1){
   Waveform = SINE;
 } else if ( FormSW_B ==1 ){
   Waveform = SQUARE;
 } else {
   Waveform = TRIANGLE;
 }

//waveform SPI sending

 if ( old_Waveform != Waveform){
   AD9833setFrequency(frequency,Waveform);
 }


//freq Range setting
 
 RangeA = digitalRead(7);
 RangeB = digitalRead(6);

 old_freqRange=freqRange;

 if ( RangeA == 1 ){
   freqRange = 70;
 } else if ( RangeB == 1 ){
   freqRange = 20000;
 } else {
   freqRange = 1000;
 }

 if ( old_freqRange != freqRange){
   AD9833setFrequency(frequency,Waveform);
 }


//VR frequency setting
 old_frequency = frequency ;
 
 frequency = analogRead(0); //set frequency;

//frequency SPI sending
//if there is no freq changes , not send SPI data

 if ( old_frequency - frequency > 2){ 
 AD9833setFrequency(frequency,Waveform);
 }else if (frequency - old_frequency > 2){
   AD9833setFrequency(frequency,Waveform);
 }else{
   delay(10);
 }
 delay(10);

}

// AD9833 documentation advises a 'Reset' on first applying power.
void AD9833reset() {
 WriteRegister(0x100);   // Write '1' to AD9833 Control register bit D8.
 delay(10);
}

// Set the frequency and waveform registers in the AD9833.
void AD9833setFrequency(long frequency, int Waveform) {

 long FreqWord = (1 + frequency * frequency * pow(2, 28)) / refFreq / freqRange;

 int MSB = (int)((FreqWord & 0xFFFC000) >> 14);    //Only lower 14 bits are used for data
 int LSB = (int)(FreqWord & 0x3FFF);
  
 //Set control bits 15 ande 14 to 0 and 1, respectively, for frequency register 0
 LSB |= 0x4000;
 MSB |= 0x4000; 
  

 WriteRegister(LSB);                  // Write lower 16 bits to AD9833 registers
 WriteRegister(MSB);                  // Write upper 16 bits to AD9833 registers.
 WriteRegister(0xC000);               // Phase register
 WriteRegister(Waveform);             // Exit & Reset to SINE, SQUARE or TRIANGLE

}

void WriteRegister(int dat) { 
  
 // Display and AD9833 use different SPI MODES so it has to be set for the AD9833 here.
 SPI.setDataMode(SPI_MODE2);       
  
 digitalWrite(FSYNC, LOW);           // Set FSYNC low before writing to AD9833 registers
 delayMicroseconds(10);              // Give AD9833 time to get ready to receive data.
  
 SPI.transfer(highByte(dat));        // Each AD9833 register is 32 bits wide and each 16
 SPI.transfer(lowByte(dat));         // bits has to be transferred as 2 x 8-bit bytes.

 digitalWrite(FSYNC, HIGH);          //Write done. Set FSYNC high
}​
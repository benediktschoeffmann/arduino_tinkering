
#include "MyEncoder.h"

#define CLK 2
#define DT  3
#define SW  4

MyEncoder encoder = MyEncoder(CLK, DT, SW);
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("Start");

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char result = encoder.process();
  if (result == DIR_CW) {
    counter++;
    Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
    Serial.println(counter);
  }

  if (result & DIR_SW) {
    Serial.println("Button");
  }

}

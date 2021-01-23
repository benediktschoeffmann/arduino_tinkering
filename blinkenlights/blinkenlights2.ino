
// Basic Test - Part 2

// Now, we add the clock signal. A CD2024, a 7-stage binary ripple-carry counter, translates this into ta binary number,
// which we use as SELECT for the CD4051
// Connect PINS 4,5,6 to S0 = 11, S1 = 10, S2 = 9 of a CD4051 which triggers a LED. 

// clock speed is determined by a potentiometer on A0

#define TEMPO_POT A0
#define CLOCK     3



void setup() {

  pinMode(TEMPO_POT, INPUT);
  pinMode(CLOCK, OUTPUT);

  
  // Via serial we can f.i. send sensordata back from the arduino.
  // initialize comminocation with 9k6 baud. 
  Serial.begin(9600);s
}

void loop() {

  int val = analogRead(TEMPO_POT);
  Serial.println(val);

}

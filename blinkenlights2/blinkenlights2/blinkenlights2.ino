
// Basic Test - Part 2

// Now, we add the clock signal. A CD2024, a 7-stage binary ripple-carry counter, translates this into ta binary number,
// which we use as SELECT for the CD4051
// Connect PINS 4,5,6 to S0 = 11, S1 = 10, S2 = 9 of a CD4051 which triggers a LED. 

// clock speed is determined by a potentiometer on A0

#define TEMPO_POT A0
#define CLOCK     3

int clockState;
int BPM;
double quarterNoteDuration; // in ms

void setup() {

  pinMode(TEMPO_POT, INPUT_PULLUP);
  pinMode(CLOCK, OUTPUT);

  // Via serial we can f.i. send sensordata back from the arduino.
  // initialize comminocation with 9k6 baud. 
  Serial.begin(9600);
  clockState = 0;
}

void loop() {

  digitalWrite(CLOCK, (clockState++) % 2);

  BPM = analogRead(TEMPO_POT);
  Serial.print(BPM);
  Serial.print(" | | " );
  BPM = map(BPM, 0, 1023, 80, 200);
  Serial.print(BPM);
  quarterNoteDuration = (60000)/(BPM*4);
  Serial.print(" | | " );
  Serial.println(quarterNoteDuration/1000);
  delay(quarterNoteDuration);

  // delay(quarterNoteDutration);

}

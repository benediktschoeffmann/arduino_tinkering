
// Basic Test 
// Connect PINS 4,5,6 to S0 = 11, S1 = 10, S2 = 9 of a CD4051 which triggers a LED

#define B0 5  // binary Zero
#define B1 6  // binary Two
#define B2 7  // binary Four

#define DELAY 100

void setup() {

  pinMode(B0, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

}

void loop() {

  for (int i = 0; i < 8; i++) {

    if (i & 1) {
      digitalWrite(B0, HIGH);
    }
    if (i & 2) {
      digitalWrite(B1, HIGH);
    }
    if (i & 4) {
      digitalWrite(B2, HIGH);
    }

    delay(DELAY);

    digitalWrite(B0, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
  }

}

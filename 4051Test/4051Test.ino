
#define POT_PIN A1

#define SEL_A_PIN 10
#define SEL_B_PIN 11
#define SEL_C_PIN 12

int pots[8] = {1024, 1024, 512, 512, 512, 512, 512,512};
int tempo;

void setup() {
  Serial.begin(9600);
  pinMode(SEL_A_PIN, OUTPUT);
  pinMode(SEL_B_PIN, OUTPUT);
  pinMode(SEL_C_PIN, OUTPUT);

}

void debug() {
  Serial.print(pots[0]);
  Serial.print("\t");
  Serial.print(pots[1]);
  Serial.print("\t");
  Serial.print(pots[2]);
  Serial.print("\t");
  Serial.print(pots[3]);
  Serial.print("\t");
  Serial.print(pots[4]);
  Serial.print("\t");
  Serial.print(pots[5]);
  Serial.print("\t");
  Serial.print(pots[6]);
  Serial.print("\t");
  Serial.println(pots[7]);
}


void loop() {
  getPots();
}

void getPots() {
  for (int i = 0; i<8; i++) {
    digitalWrite(SEL_A_PIN, bitRead(i, 0));
    digitalWrite(SEL_B_PIN, bitRead(i, 1));
    digitalWrite(SEL_C_PIN, bitRead(i, 2));
    

    pots[i] = analogRead(POT_PIN);

    Serial.print(pots[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

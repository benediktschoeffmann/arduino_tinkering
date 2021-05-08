
// used encoder: KY040

#define CLK 2
#define DT  3
#define SW  4

int lastClk = 0;
int curClk = 0;
boolean isFirst = true;
boolean clockwise;

void setup() {    
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  pinMode(SW, INPUT);
  
  digitalWrite(SW, HIGH);
  digitalWrite(DT, HIGH);
  digitalWrite(CLK, HIGH);
  
  lastClk = digitalRead(CLK);
 
  Serial.begin(115200);
}

void loop() {

  curClk = digitalRead(CLK);

  if (curClk != lastClk) {

    if (digitalRead(DT) != curClk) {
      // CLK changed first, turn right
      clockwise = true;  
    } else {
      // turn left
      clockwise  = false;
    }

    // is used for weird double signal
    if (isFirst) {
      debug( (clockwise  == true) ? "clockwise " : "counter clockwise");
    }

    isFirst = !isFirst;
    // delay(200);
  }

  // check for click
  if (!digitalRead(SW) ) {
     debug("Clicked ! ");
     delay(100);  // debounce
  }

  lastClk = curClk;
}

void debug(const char* msg) {
  Serial.println(msg);
}

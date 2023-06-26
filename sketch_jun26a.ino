#define outPin 13
int intensity = 20;
unsigned long timeRefHigh = 0;
unsigned long timeRefLow = 0;
int high0 = 0;
int high1 = 0;
int state = 0;


void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, HIGH);
  timeRefHigh = millis();
  timeRefLow = millis();
}

void loop() {
  unsigned long cas = millis();
  high0 = (timeRefHigh + 0 + intensity) - cas;
  high1 = (timeRefLow + 200 - intensity) - cas;
  Serial.println(high1);
  timers();
}

void timers() {

  //high pulz
  if (high0 <= 0) {
    timeRefHigh = millis();
    digitalWrite(outPin, LOW);
     if (state = 2) {
      expesiveOperation();
    }
  }

  //low pulz
  if (high1 <= 0) {
    timeRefLow = millis();
    digitalWrite(outPin, HIGH);
    if (state = 0) {
      expesiveOperation();
    }
    if(state = 1){
      expesiveOperation();
    }
  }
}


void readInput() {
  if (Serial.available() > 1) {
    intensity = Serial.parseInt();
    Serial.println(intensity);
    if (intensity < 60) {
      state = 0;
    }
    if (120 > intensity > 60) {
      state = 1;
    }
    if (intensity > 120) {
      state = 2;
    }
  }
}




void expesiveOperation() {
  readInput();
  // for (int i = 0; i < 15; i++) {
  //   readInput();
  //   Serial.println("imexpensive");
  // }
}

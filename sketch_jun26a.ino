#define outPin 2
int intensity = 50;
unsigned long timeRefHigh = 0;
unsigned long timeRefLow = 0;
int highPulsTimer = 0;
int lowPulseTimer = 0;
int ifintensity0 = 0;
int ifintensity1 = 0;
int state = 0;
int mappingTable[] = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, 41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61, 61, 62, 63, 64, 65, 66, 67, 68, 69, 71, 71, 72, 73, 74, 75, 76, 77, 78, 79, 81, 81, 82, 83, 84, 85, 86, 87, 88, 89, 91, 91, 92, 93, 94, 95, 96, 97, 98, 99, 101, 101, 102, 103, 104, 105, 106, 107, 108, 109, 111, 111, 112, 113, 114, 115, 116, 117, 118, 119, 121, 121, 122, 123, 124, 125, 126, 127, 128, 129, 131, 131, 132, 133, 134, 135, 136, 137, 138, 139, 141, 141, 142, 143, 144, 145, 146, 147, 148, 149, 151, 151, 152, 153, 154, 155, 156, 157, 158, 159, 161, 161, 162, 163, 164, 165, 166, 167, 168, 169, 171, 171, 172, 173, 174, 175, 176, 177, 178, 179, 181, 181, 182, 183, 184, 185, 186, 187, 188, 189, 191, 191, 192, 193, 194, 195, 196, 197, 198, 199, 199};


void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, HIGH);
  timeRefHigh = millis();
  timeRefLow = millis();
}

void loop() {
  unsigned long cas = millis();
  highPulsTimer = timeRefHigh + intensity - cas;
  lowPulseTimer = timeRefLow + 200 - intensity - cas;
  timers();
}

void timers() {

  //high pulz
  if (highPulsTimer <= 0) {
    timeRefHigh = millis();
    digitalWrite(outPin, LOW);
    if (state == 1) {
      readInput();
    }
  }

  //low pulz
  if (lowPulseTimer <= 0) {
    timeRefLow = millis();
    digitalWrite(outPin, HIGH);

    if (state == 0) {
      readInput();
    }
  }
}


void readInput() {
  // if (Serial.available() > 0) {
  //   intensity = Serial.parseInt();
  //   Serial.println(intensity);
    intensity = mappingTable[intensity];
    ifintensity0 = intensity - 100;
    ifintensity1 = intensity - 100;
    Serial.println(intensity);
    if (ifintensity0 >= 0) {
      state = 0;
    }
    if (ifintensity1 < 0) {
      state = 1;
    }

}




void expesiveOperation() {
  readInput();
  // Serial.print("1: ");
  // Serial.println(high0);
  // Serial.print("2: ");
  // Serial.println(high1);
  // for (int i = 0; i < 3; i++) {
  //   Serial.println("imexpensive");
  // }
}

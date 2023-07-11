
#include <LCD_I2C.h>
#define outPin 2
int readIntensity = 20;
int intesity = 200;
unsigned long timeRefHigh = 0;
unsigned long timeRefLow = 0;
unsigned long timeRefLcd = 0;
unsigned long timeRefInterpolation = 0;
int highPulsTimer = 0;
int lowPulseTimer = 0;
int interpolationTimer = 0;
int lcdTimer = 0;
int ifintensity0 = 0;
int ifintensity1 = 0;
int state = 0;
int mappingTable[] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
LCD_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  pinMode(7, INPUT);
  pinMode (A0, INPUT);
  digitalWrite(outPin, LOW);
  timeRefHigh = millis();
  timeRefLow = millis();
  lcd.begin();  // If you are using more I2C devices using the Wire library use lcd.begin(false)
                // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
}

void loop() {
  unsigned long cas = millis();
  //change readIntensity to real intensity;
  highPulsTimer = timeRefLow + intesity - cas;
  lowPulseTimer = timeRefLow + 200 - cas;
  lcdTimer = timeRefLcd + 500 - cas;
  interpolationTimer = timeRefInterpolation + 500 - cas;
  //pocitat cas od jednoho bodu kekw a nebo spravne xD KEKW
  
  timers();
}

void timers() {

  //high pulz
  if (highPulsTimer <= 0) {
    // timeRefHigh = millis();
    digitalWrite(outPin, HIGH);
    if (state == 1) {
      readInput();
    }
  }

  //low pulz
  if (lowPulseTimer <= 0) {
    timeRefLow = millis();
    digitalWrite(outPin, LOW);

    if (state == 0) {
      readInput();
    }
  }

  //low pulz
  if (interpolationTimer <= 0) {
    timeRefInterpolation = millis();
    int val = readIntensity - intesity;
    if(val > 0)
    {
      intesity += 1;
    }
    if(val < 0)
    {
      intesity -= 1;
    }
  }
}


void readInput() {
  // if (Serial.available() > 0) {
  //   intensity = Serial.parseInt();
  //   // intensity = mappingTable[intensity];
  //   Serial.println(intensity);
  //   ifintensity0 = intensity - 100;
  //   ifintensity1 = intensity - 100;
  //   if (ifintensity0 >= 0) {
  //     state = 0;
  //   }
  //   if (ifintensity1 < 0) {
  //     state = 1;
  //   }
  // }
  if (digitalRead(7) == 0) {
    readIntensity = analogRead(A0);
    
    readIntensity = readIntensity - 700;
    readIntensity = readIntensity * 0.65;
    if(readIntensity >= 200)
    {
      readIntensity = 200;
    }
    if(readIntensity <= 0){
      readIntensity = 0;
    }
    readIntensity = mappingTable[readIntensity];
    
    if (lcdTimer <= 0) {
      timeRefLcd = millis();
      lcd.setCursor(0, 0);
      lcd.print("SPD ");  // You can make spaces using well... spaces
      lcd.setCursor(4, 0);
      lcd.print("   "); // Or setting the cursor in the desired position.
        lcd.setCursor(4, 0);
      lcd.print(readIntensity);
      lcd.setCursor(9, 0);
      lcd.print("stv zap");
    }
  } else {
    readIntensity = 0;
    if (lcdTimer <= 0) {
      timeRefLcd = millis();
    lcd.setCursor(0, 0);
    lcd.print("SPD ");  // You can make spaces using well... spaces
    lcd.setCursor(4, 0);
    lcd.print("   ");  // Or setting the cursor in the desired position.
      lcd.setCursor(4, 0);
    lcd.print(readIntensity);
    lcd.setCursor(9, 0);
    lcd.print("stv vyp");
    }
  }
  // Serial.println(intensity);

  ifintensity0 = readIntensity - 100;
  ifintensity1 = readIntensity - 100;
  if (ifintensity0 >= 0) {
    state = 0;
  }
  if (ifintensity1 < 0) {
    state = 1;
  }
}




void expesiveOperation() {
  readInput();
}

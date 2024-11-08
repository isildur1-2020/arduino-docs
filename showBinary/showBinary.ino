#define NUM_PINS 4

boolean hexadecimalNumbers[16][NUM_PINS] = {
    { 0, 0, 0, 0 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 1 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 1, 1, 0, 0 },
    { 1, 1, 0, 1 },
    { 1, 1, 1, 0 },
    { 1, 1, 1, 1 }
  };

void setPinesToOutput(int min, int max) {
  for(byte i = min; i <= max; i++) {
    pinMode(i, OUTPUT);
  } 
}

void turnOnLEDS(boolean status[]) {
  for(byte i = 0; i < 4; i++) {
    byte currentLed = i + 2;
    digitalWrite(currentLed, status[i] ? HIGH : LOW);
  }
}

void setup() {
  setPinesToOutput(2, 5);
}

void loop() {
  for(byte i = 0; i < 16; i++) {
    turnOnLEDS(hexadecimalNumbers[i]);
    delay(1500);
  }
}

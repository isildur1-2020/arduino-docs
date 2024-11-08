#define PIN_3 3
#define MORSE_DOT_DELAY 100
#define MORSE_DASH_DELAY 300
#define MORSE_WORD_DELAY 2000
#define MORSE_PIN PIN_3

void turnOn(int waitTime) {
  digitalWrite(MORSE_PIN, HIGH);
  delay(waitTime);
}

void turnOff(int waitTime) {
  digitalWrite(MORSE_PIN, LOW);
  delay(waitTime);
}

void printDot() {
  turnOn(MORSE_DOT_DELAY);
  turnOff(MORSE_DOT_DELAY);
}

void printDash() {
  turnOn(MORSE_DASH_DELAY);
  turnOff(MORSE_DASH_DELAY);
}

void setup() {
  pinMode(PIN_3, OUTPUT);
}

void loop() {
  printDot();
  printDot();
  printDot();

  printDash();
  printDash();
  printDash();

  printDot();
  printDot();
  printDot();

  delay(MORSE_WORD_DELAY);
}

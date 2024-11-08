#define LED_9 9
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0

void setup() {
  pinMode(LED_9, OUTPUT);
}

void increaseBrightness(byte led) {
  for (byte i = MIN_BRIGHTNESS; i<MAX_BRIGHTNESS; i++) {
    analogWrite(led, i);
    delay(40);
  }
}

void loop() {
  increaseBrightness(LED_9);
}
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define DHTTYPE DHT22
#define PIR_PIN 8

class SensorDHT22 {
private:
  static const int DHTPIN = 2;
  DHT dht;
public:
  SensorDHT22() : dht(DHTPIN, DHTTYPE) {
    dht.begin();
  }
  float getTemperature() {
    return dht.readTemperature();
  }
  float getHumidity() {
    return dht.readHumidity();
  }
};

class OLED {
private:
  static const int SCREEN_WIDTH = 128;  
  static const int SCREEN_HEIGHT = 64;  
  static const int OLED_RESET = -1;     
  Adafruit_SSD1306 display;
public:
  OLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      for (;;);
    }
    this->clean();
  }
  void render(String message, int yPosition) {
    display.setCursor(0, yPosition);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print(message);
    display.display();
  }
  void clean() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
  }
};

OLED* display;
SensorDHT22* dht;

unsigned long previousMillis = 0;
const long interval = 2000; // Actualizar cada 2 segundos
bool motionDetected = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing..");
  display = new OLED();
  dht = new SensorDHT22;
  pinMode(PIR_PIN, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check for motion every cycle
  bool motionState = digitalRead(PIR_PIN) == HIGH;
  if (motionState != motionDetected) {
    motionDetected = motionState;
    display->clean();
    String motionMsg = motionDetected ? "Mot: Yes" : "Mot: No";
    display->render(motionMsg, 32); // Render motion message
  }

  // Update temperature and humidity every interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float t = dht->getTemperature();  
    float h = dht->getHumidity();     

    display->clean();
    String temperatureMsg = "Tmp:" + String(t) + "C";
    String humidityMsg = "Hum:" + String(h) + "%";
    display->render(temperatureMsg, 0);  
    display->render(humidityMsg, 16);    
    display->render(motionDetected ? "Mot: Yes" : "Mot: No", 32);
  }
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED {
private:
  static const int SCREEN_WIDTH = 128;  // OLED display width, in pixels
  static const int SCREEN_HEIGHT = 64;  // OLED display height, in pixels
  static const int OLED_RESET = -1;     // Reset pin # (or -1 if sharing Arduino reset pin)
  Adafruit_SSD1306 display;
public:
  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  OLED()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;)
        ;  // Don't proceed, loop forever
    }
    this->clean();
  }
  void render(String message) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println(message);
    display.display();
  }
  void clean() {
    display.clearDisplay();
    display.display();
  }
};

void setup() {
  Serial.begin(9600);
  OLED oled;
  oled.render("This is an example");
}

void loop() {}
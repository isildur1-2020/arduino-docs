#include "DHT.h"
//#define DHTTYPE DHT11   // uncomment if use DHT 11
#define DHTTYPE DHT22

class SensorDHT22 {
private:
  static const int DHTPIN = 2;
  DHT dht;
public:
  SensorDHT22()
    : dht(DHTPIN, DHTTYPE) {
    dht.begin();
  }
  float getTemperature() {
    return dht.readTemperature();
  }
  float getHumidity() {
    return dht.readHumidity();
  }
};

SensorDHT22 dht;

void setup() {
  Serial.begin(9600);
}
void loop() {
  delay(2000);
  float t = dht.getTemperature();  //Leemos la temperatura en grados Celsius
  float h = dht.getHumidity();     //Leemos la Humedad
  String message = "Temperatura: " + String(t) + " - " + "Humedad: " + String(h);  
  Serial.println(message);
}

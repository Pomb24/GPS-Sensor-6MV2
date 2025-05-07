#include <Arduino.h>
#include <TinyGPS++.h>

// Khai báo UART với GPS
HardwareSerial Serial2(PA3, PA2);  // RX, TX

TinyGPSPlus gps;

unsigned long lastDataTime = 0;
const int samplingInterval = 5000;

void setup() {
  Serial.begin(9600);      // Giao tiếp với PC
  Serial2.begin(9600);     // Giao tiếp với GPS
}

void loop() {
  while (Serial2.available()) {
    char c = Serial2.read();  // Đọc dữ liệu từ GPS
    gps.encode(c);   // Đưa dữ liệu vào parser
    unsigned long currentTime = millis();

    if (currentTime - lastDataTime >= samplingInterval) {
      lastDataTime = currentTime;
    if (gps.location.isUpdated()) {
      Serial.println("\n✅ Tọa độ mới:");
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("Valid: ");
      Serial.print(gps.location.isValid());
      Serial.print("  Updated: ");
      Serial.println(gps.location.isUpdated());
    }
  }
}

}
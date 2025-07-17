#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// === Sensor Pins ===
#define MQ7_PIN A0
#define MQ135_PIN A1
#define DUST_SENSOR_PIN A2

// === GPS Communication ===
SoftwareSerial gpsSerial(4, 3); // RX, TX
TinyGPSPlus gps;

void setupSensors() {
  pinMode(MQ7_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  pinMode(DUST_SENSOR_PIN, INPUT);
}

void readAirQualitySensors(int& coValue, int& airQualityValue, int& dustValue) {
  coValue = analogRead(MQ7_PIN);
  airQualityValue = analogRead(MQ135_PIN);
  dustValue = analogRead(DUST_SENSOR_PIN);
}

void printLocation() {
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  } else {
    Serial.println("Waiting for GPS fix...");
  }
}

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  setupSensors();
  Serial.println("Real-Time Pollution Monitoring System Started");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  int co, airQuality, dust;
  readAirQualitySensors(co, airQuality, dust);

  Serial.println("=== Environmental Data ===");
  printLocation();
  Serial.print("CO Level (MQ7): ");
  Serial.println(co);
  Serial.print("Air Quality (MQ135): ");
  Serial.println(airQuality);
  Serial.print("Dust Level: ");
  Serial.println(dust);
  Serial.println("==========================");

  delay(5000);  // Log every 5 seconds
}

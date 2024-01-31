#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL50v9YB7Gu"
#define BLYNK_TEMPLATE_NAME "GERNAIN"
#define BLYNK_AUTH_TOKEN "8wnWzji7YPcl8lslcKNjImBYO2BRGzJi"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Define the pins that we will use
#define SENSOR 33
#define LED 26
#define DHTTYPE DHT11

DHT_Unified dht(SENSOR, DHTTYPE);

char ssid[] = "iPhone de Germain";
char pass[] = "caca1234";

void setup() {
  // Setup pins
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Begin serial communication
  Serial.begin(9600);
  delay(100);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.run();

  // Start listening to the DHT11
  dht.begin();

  sensors_event_t event;

  // Get temperature event and print its value
  float temp_measure = -999.0;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    temp_measure = event.temperature;
  }

  // Get humidity event and print its value.
  float relative_humidity_measure = -999.0;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    relative_humidity_measure = event.relative_humidity;
  }

  if (!isnan(temp_measure)) {
    Blynk.virtualWrite(V1, temp_measure);  
  }

  if (!isnan(relative_humidity_measure)) {
    Blynk.virtualWrite(V0, relative_humidity_measure); 
  }

  Serial.println("Going to sleep for 5 seconds...");
  delay(100);
  ESP.deepSleep(5e6);
}

void loop() {
  // Not needed anymore, the function is kept so PlatformIO does not complain.
}
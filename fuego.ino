// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "Adafruit_Sensor.h"
#include "DHT.h"
#include "DHT_U.h"
#include <ESP8266WiFi.h>          // ESP8266 base Wi-Fi library 
#include <ESP8266WebServer.h>     // WebServer library
#include <FS.h>    
#define heatindex_alert 32
#define DHTPIN 5     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);      // create a server at port 80
unsigned long previousMillis;

uint32_t delayMS;

float computeHeatIndex(float temperature, float percentHumidity,bool isFahrenheit=1) {
  float hi;


  hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) +
              (percentHumidity * 0.094));

  if (hi > 79) {
    hi = -42.379 + 2.04901523 * temperature + 10.14333127 * percentHumidity +
         -0.22475541 * temperature * percentHumidity +
         -0.00683783 * pow(temperature, 2) +
         -0.05481717 * pow(percentHumidity, 2) +
         0.00122874 * pow(temperature, 2) * percentHumidity +
         0.00085282 * temperature * pow(percentHumidity, 2) +
         -0.00000199 * pow(temperature, 2) * pow(percentHumidity, 2);

    if ((percentHumidity < 13) && (temperature >= 80.0) &&
        (temperature <= 112.0))
      hi -= ((13.0 - percentHumidity) * 0.25) *
            sqrt((17.0 - abs(temperature - 95.0)) * 0.05882);

    else if ((percentHumidity > 85.0) && (temperature >= 80.0) &&
             (temperature <= 87.0))
      hi += ((percentHumidity - 85.0) * 0.1) * ((87.0 - temperature) * 0.2);
  }

  return hi;
}


void setup() {
  Serial.begin(9600);
  StartWifi();
  startServer();
  if (!SPIFFS.begin()) {
        Serial.println("ERROR - File system initialization failed!");
        return;    // init failed
  }
  pinMode(D2,OUTPUT);
  pinMode(D0,OUTPUT);
  pinMode(D7,OUTPUT);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); 
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); 
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution);
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  delay(5000);
  digitalWrite(D7,HIGH);
}

float hd;
float rel_h;
float temp;
/* 
    rel_h=event.relative_humidity;
    hd=computeHeatIndex(event.temperature,event.relative_humidity);
*/
void loop() {
  sensors_event_t event;
  server.handleClient(); 
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)){
    Serial.println("couldn't read temp.");
  }else{
    temp=event.temperature;
  }
  if(isnan(event.relative_humidity)){ //Why is the relative humidaity the same as temp? 21.90? just a weird fluke?
    Serial.println("couldn't read hum.");
  }else{
    rel_h=event.relative_humidity;
  }
  if(isnan(computeHeatIndex(temp,rel_h))){
    Serial.println("couldn't read heatindex");
  }else{
    hd=computeHeatIndex(temp,rel_h);
  }

  
  const long interval = 1000;   
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    Serial.print("Heat Index: ");Serial.println(hd);
    Serial.print("rel_ hum: ");Serial.println(rel_h);
    Serial.print("temp ");Serial.println(temp);
    if (hd>heatindex_alert) {
      Serial.println("BUZZZ");
      Serial.println("LEEDD");
      digitalWrite(D2,1);
      digitalWrite(D0,1);
    } else {
      digitalWrite(D2,0);
      digitalWrite(D0,0);
    }
  }
}
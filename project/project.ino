#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <time.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>
#include <lvgl.h>
#include <initGUI.h>

#include "apiLogic/ApiHandling.h"

// Wi-Fi credentials (Delete these before commiting to GitHub)
static const char* WIFI_SSID = "";
static const char* WIFI_PASSWORD = "";

LilyGo_Class amoled;

// Function: Connects to WIFI
static void connect_wifi()
{
  Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  const uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < 15000) {
    delay(250);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected.");
  } else {
    Serial.println("WiFi could not connect (timeout).");
  }
}

// Must have function: Setup is run once on startup
void setup()
{
  Serial.begin(115200);
  delay(200);

  if (!amoled.begin()) {
    Serial.println("Failed to init LilyGO AMOLED.");
    while (true) delay(1000);
  }

  beginLvglHelper(amoled);   // init LVGL for this board
  constructUi();             // construct initial UI
  //connect_wifi();

  connect_wifi();

  APIhandler handler;
  vector<StationObject> stationsArray = handler.getStationsArray(30, 1);
  StationObject station = handler.getStationFromArray(stationsArray, "Abelvattnet Aut");
  Serial.println("name: " + String(station.getName().c_str()) + " longitude: " + String(station.getLon()) + " latitude: " + String(station.getLat()));
  vector<ForecastObject> forecasts = handler.getForecastNext7Days(station); 
}

// Must have function: Loop runs continously on device after setup
void loop()
{
  delay(lv_timer_handler());
}
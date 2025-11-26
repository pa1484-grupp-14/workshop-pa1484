#include <time.h>
#include <HAL.hpp>
#include "initGUI.h"

static hal::Display* amoled;

// Function: Connects to WIFI
static void connect_wifi() {
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

#ifndef PIO_UNIT_TESTING


// Must have function: Setup is run once on startup
void setup() {
  amoled = new hal::Display();
  hal::init(amoled);

  connect_wifi();
  constructUi();
}




// Must have function: Loop runs continously on device after setup
void loop() {
  int wanted_duration = lv_timer_handler();
  int next_iteration = wanted_duration + millis();

  int wait = next_iteration - millis();
  if ( wait > 0 ) {
    delay(wait);
  }
}

#endif

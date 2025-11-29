#include <time.h>
#include <HAL.hpp>
#include "prelude.h"

static hal::Display* amoled;

// Function: Connects to WIFI
static void connect_wifi() {
  Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

#ifndef PIO_UNIT_TESTING

// Must have function: Setup is run once on startup


void setup() {
  amoled = new hal::Display();
  hal::init(amoled);

  GUI& gui = getGui();
  connect_wifi();
  //init
  gui.init();

  getMainScreen().constructUI(&gui.addTile());
  getForecastScreen().constructUI(&gui.addTile());
  getWeatherChartScreen().constructUI(&gui.addTile());
  getSettingsScreen().constructUI(&gui.addTile());

  gui.scrollToTile(0);
}

// Must have function: Loop runs continously on device after setup
void loop() {
  int wait = lv_timer_handler() + millis();
  while (millis() < wait) {
    getMainScreen().process();
    getForecastScreen().process();
    getWeatherChartScreen().process();
    getSettingsScreen().process();
  }
}

#endif

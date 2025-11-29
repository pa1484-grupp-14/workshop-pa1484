#include <time.h>
#include <HAL.hpp>
#include "initGUI.h"
#include "components/prelude.h"

static hal::Display* amoled;

// Function: Connects to WIFI
static void connect_wifi() {
  Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

#ifndef PIO_UNIT_TESTING
// Must have function: Setup is run once on startup
MainScreen *mainScreen;
Forecast *forecast;
WeatherChart* weatherChart;
Settings* settings;

void setup() {
  amoled = new hal::Display();
  hal::init(amoled);

  connect_wifi();
    //init
  gui.init();
  
  mainScreen = new MainScreen();
  mainScreen->constructUI(&gui.addTile());

  forecast = new Forecast();
  forecast->constructUI(&gui.addTile());

  weatherChart = new WeatherChart();
  weatherChart->constructUI(&gui.addTile());

  settings = new Settings();
  settings->constructUI(&gui.addTile());

  gui.scrollToTile(0);
}

// Must have function: Loop runs continously on device after setup
void loop() {
  int wait = lv_timer_handler() + millis();
  while(millis() < wait) {
    mainScreen->process();
    forecast->process();
    weatherChart->process();
    settings->process();
  }
}
#endif

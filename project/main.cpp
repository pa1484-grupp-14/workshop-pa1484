#include <time.h>
#include <HAL.hpp>
#include "prelude.h"
#include <iostream>

static hal::Display* amoled;

// Function: Connects to WIFI
static void connect_wifi() {
  std::cout << "Connecting to WiFi SSID: " << WIFI_SSID << std::endl;
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
  //std::cout << "doing frame: " << wait << std::endl;
  while (millis() < wait) {
    
    getMainScreen().process();
    getForecastScreen().process();
    getWeatherChartScreen().process();
    getSettingsScreen().process();
    
  }
}

#endif
#ifndef LILYGO_BUILD
unsigned int tick_cb() {
  return millis();
}
void WinMain() {
  
  #include <SDL2/SDL.h>
  
  setup();
  lv_tick_set_cb(tick_cb);
  while(true) {
    auto a = millis();
    if(amoled->handle_events()) return;
    loop();
    lv_task_handler();
    auto b = millis();
    lv_tick_inc(b-a);
  }
}
#endif

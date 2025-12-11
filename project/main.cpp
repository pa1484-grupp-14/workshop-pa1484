#include <time.h>
#include <HAL.hpp>
#include "prelude.h"
#ifdef LILYGO_BUILD
#include <LittleFS.h>
#endif
#ifdef NATIVE_BUILD
#include "nativeReplacements/LittleFS.h"
#endif
#ifdef WINDOWS_BUILD
#include <winbase.h>
#endif

#define FORMAT_LITTLEFS_IF_FAILED true
#include <iostream>

static hal::Display* amoled;

// Function: Connects to WIFI
static void init_wifi() {
  std::cout << "Connecting to WiFi SSID: " << WIFI_SSID << std::endl;
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void init_FS() {
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    std::cout << "[main] LittleFS Mount Failed" << std::endl;
  }
}

#ifndef PIO_UNIT_TESTING

// Must have function: Setup is run once on startup
void setup() {
  amoled = new hal::Display();
  //Initialize Hardware
  hal::init(amoled);
  init_FS();  
  init_wifi();

  //Initialize GUI
  GUI& gui = getGui();
  gui.init();

  //construct all of the tiles in the GUI
  getMainScreen().constructUI(&gui.addTile());
  getForecastScreen().constructUI(&gui.addTile());
  getWeatherChartScreen().constructUI(&gui.addTile());
  getSettingsScreen().constructUI(&gui.addTile());

  //scroll to the main tile
  gui.scrollToTile(0);
}

// Must have function: Loop runs continously on device after setup
void loop() {
  // find out at what millis value next loop should occur to satisfy LVGL
  int wait = lv_timer_handler() + millis();

  //process main screen
  int time_a = millis();
  getMainScreen().process();

  //=||= forecast screen
  int time_b = millis();
  getForecastScreen().process();

  //=||= weather chart screen
  int time_c = millis();
  getWeatherChartScreen().process();

  //=||= settings screen
  int time_d = millis();
  getSettingsScreen().process();

  //=||= background API calls
  int time_e = millis();
  do {
    APIhandler::process();
  } while (millis() < wait);
  int time_f = millis();

  //if this all took more than 200ms, profile it so we see what took so long
  if (time_f - time_a > 200) {
    std::cout << "[WARNING] profiling for long frame:" << std::endl;
    std::cout << "[WARNING] main: " << time_b - time_a << std::endl;
    std::cout << "[WARNING] forecast: " << time_c - time_b << std::endl;
    std::cout << "[WARNING] weather chart: " << time_d - time_c << std::endl;
    std::cout << "[WARNING] settings: " << time_e - time_d << std::endl;
    std::cout << "[WARNING] API processing:" << time_f - time_e << std::endl;
  }
}

#endif
#ifndef LILYGO_BUILD
unsigned int tick_cb() {
  return millis();
}
int main() {
#include <SDL2/SDL.h>

  setup();
  lv_tick_set_cb(tick_cb);
  while (true) {
    auto a = millis();
    if (amoled->handle_events())
      return 0;
    loop();
    lv_task_handler();
    auto b = millis();
    lv_tick_inc(b - a);
  }
}
#ifdef WINDOWS_BUILD
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
            int nShowCmd) {
  return main();
}
#endif
int _start() {
  return main();
}
#endif

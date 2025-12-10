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
static void connect_wifi() {
  std::cout << "Connecting to WiFi SSID: " << WIFI_SSID << std::endl;
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void init_FS(){
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    std::cout << "[main] LittleFS Mount Failed" << std::endl;
  }
}

#ifndef PIO_UNIT_TESTING

// Must have function: Setup is run once on startup
void setup() {
  amoled = new hal::Display();
  hal::init(amoled);
  init_FS();

  GUI& gui = getGui();
  connect_wifi();
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
  int a = millis();
  getMainScreen().process();
  int b = millis();
  getForecastScreen().process();
  int c = millis();
  getWeatherChartScreen().process();
  int d = millis();
  getSettingsScreen().process();
  int e = millis();
  //std::cout << "doing frame: " << wait << std::endl;
  do {
    APIhandler::process();
  } while (millis() < wait);
  int f = millis();

  if (f-a > 100) {
    std::cout << "[WARNING] frame took unreasonably long, heres the timings:" << std::endl;
    std::cout << "[WARNING]" << b-a << " " << c-b << " " << d-c << " " << e-d << " " << f-e << std::endl;
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
  while(true) {
    auto a = millis();
    if(amoled->handle_events()) return 0;
    loop();
    lv_task_handler();
    auto b = millis();
    lv_tick_inc(b-a);
  }
}
#ifdef WINDOWS_BUILD
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  return main();
}
#endif
int _start() {
  return main();
}
#endif

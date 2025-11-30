#pragma once
#include "gui/Gui.h"
#include "components/prelude.h"

unsigned long millis();

#ifndef LILYGO_BUILD


#define WIFI_STA 0
class Wifi {
    public:
    void mode(int dummy) {};
    void begin(const char* ssid, const char* pass) {};
};
static Wifi WiFi;
#endif

GUI& getGui();
MainScreen& getMainScreen();
Forecast& getForecastScreen();
WeatherChart& getWeatherChartScreen();
Settings& getSettingsScreen();
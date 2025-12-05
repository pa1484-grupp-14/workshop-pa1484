#include <WiFi.h>
#include "gui/Gui.h"
#include "components/Components.h"

static GUI gui;
static MainScreen mainScreen;
static Forecast forecastScreen;
static WeatherChart weatherChartScreen;
static Settings settingsScreen;


GUI& getGui() {
    return gui;
}
MainScreen& getMainScreen() {
    return mainScreen;
}
Forecast& getForecastScreen() {
    return forecastScreen;
}
WeatherChart& getWeatherChartScreen() {
    return weatherChartScreen;
}
Settings& getSettingsScreen() {
    return settingsScreen;
}
bool is_wifi_connected() {
    #ifdef LILYGO_BUILD
    return WiFi.status() == WL_CONNECTED;
    #else
    return true;
    #endif
}

#ifndef LILYGO_BUILD
#include <chrono>
static std::chrono::time_point<std::chrono::system_clock> start;
static bool started = false;
unsigned long millis() {
    if(!started) {
        started = true;
        start = std::chrono::system_clock::now();
    }
    auto rightNow = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = rightNow-start;
    return long(elapsed.count() * 1000.0);
}
#endif
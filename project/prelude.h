#pragma once
#ifdef LILYGO_BUILD
#include <WiFi.h>
#endif
#ifdef NATIVE_BUILD
#include "nativeReplacements/WiFi.h"
#endif
#include "components/Components.h"
#include "gui/Gui.h"
#include <string>

// utility function: returns true if the device is currently connected to wifi
bool is_wifi_connected();
// system function: returns the number of milliseconds since the program started
unsigned long millis();

void createLoadingUi(Tile* ui_tile, std::string statusText);

class MainScreen;
class Settings;
class WeatherChart;
class Forecast;

// Get the app-wide reference to the GUI class
GUI& getGui();

// Get a reference to the Main Screen of the program
MainScreen& getMainScreen();

// Get a reference to the Forecast Screen of the program
Forecast& getForecastScreen();

// Get a reference to the Weather Chart Screen of the program
WeatherChart& getWeatherChartScreen();

// Get a reference to the Setting Screen of the program
Settings& getSettingsScreen();

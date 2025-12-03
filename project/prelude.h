#pragma once
#include <WiFi.h>
#include "gui/Gui.h"
#include "components/prelude.h"

bool is_wifi_connected();
unsigned long millis();

GUI& getGui();
MainScreen& getMainScreen();
Forecast& getForecastScreen();
WeatherChart& getWeatherChartScreen();
Settings& getSettingsScreen();
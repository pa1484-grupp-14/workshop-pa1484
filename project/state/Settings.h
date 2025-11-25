#pragma once

#include <lvgl.h>
#include <string>
#include "gui/gui.h"
#include "misc/lv_types.h"

enum WeatherParameter {
  Temperature = 0,
  Wind,
  Humidity,
  Rainfall,
  SnowDepth,
  SunshineTime,
};

class Settings : public Graphical {
 private:
  WeatherParameter weather_parameter;
  std::string city;

 public:
  Settings();
  ~Settings();
  void constructUI(GUI *gui) override;
  static void change_weather_parameter(lv_event_t* event);
  static void change_city(lv_event_t* event);
};

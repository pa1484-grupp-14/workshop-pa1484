#pragma once

#include <lvgl.h>
#include <string>
#include <vector>
#include "gui/Gui.h"

enum WeatherParameter {
  Temperature = 0,
  WindSpeed = 1,
  Humidity = 2,
  Rainfall = 3,
  AirPressure = 4,
};

class Settings : public Component {
 private:
  std::vector<std::string> available_cities;
  WeatherParameter weather_parameter;
  std::string city;
  Tile* ui_tile;
 public:
  Settings();
  ~Settings();
  void constructUI(Tile *gui) override;
  void process() override;
  int getCurrentCityIndex(); 
  
  std::string getSelectedCity();
  WeatherParameter getSelectedParameter();
  static void change_weather_parameter(lv_event_t* event);
  static void change_city(lv_event_t* event);
  static void city_picker_cb(lv_event_t* event);
  static void city_confirm_cb(lv_event_t * event);
  static void city_dropdown_cb(lv_event_t * event);
  static void set_default(lv_event_t * event);
  static void reset_defaults(lv_event_t * event);
  
};

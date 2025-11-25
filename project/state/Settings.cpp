#include "Settings.h"

#include "misc/lv_event.h"
#include "widgets/dropdown/lv_dropdown.h"

// WARNING: Index of weather parameters must preserve order
void Settings::change_weather_parameter(lv_event_t* event) {
  void* dropdown = lv_event_get_target(event);
  uint32_t index = lv_dropdown_get_selected((lv_obj_t*)dropdown);
  auto settings = (Settings*)lv_event_get_user_data(event);
  settings->weather_parameter = static_cast<WeatherParameter>(index);
}

void Settings::change_city(lv_event_t* event) {
  void* obj = lv_event_get_target(event);
  const size_t buf_size = 15;
  char buf[buf_size];
  lv_dropdown_get_selected_str((lv_obj_t*)obj, buf, buf_size);
  auto settings = (Settings*)lv_event_get_user_data(event);
  settings->city = std::string(buf, buf_size);
}

#include "Settings.h"
#include "globals.h"

#include "misc/lv_event.h"
#include "widgets/dropdown/lv_dropdown.h"

Settings::Settings() {}
Settings::~Settings() {}

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

void Settings::constructUI(GUI* gui) {
  Tile& settings_tile = gui->addTile();

  // Heading
  settings_tile.setGridLayout(columns, row)
      .addLabel()
      .setText("Settings")
      .setFont(&lv_font_montserrat_48)
      .setGridCell(0, 0, 1, 2);

  settings_tile.addLabel()
      .setText("Weather parameter:")
      .setFont(&lv_font_montserrat_26)
      .setGridCell(1, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);

  settings_tile.addDropdown()
      .setOptions("Temperature\nMoisture\nWind")
      .setListFont(&lv_font_montserrat_26)
      .setFont(&lv_font_montserrat_26)
      .addEventCallback(Settings::change_weather_parameter,
                        lv_event_code_t::LV_EVENT_VALUE_CHANGED, this)
      .setGridCell(1, 1)
      .setWidth(270);

  settings_tile.addLabel("Select option 2 ")
      .setText("Weather location:")
      .setFont(&lv_font_montserrat_26)
      .setGridCell(2, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);

  settings_tile.addDropdown()
      .setOptions("Karlskrona\nGothenburg\nStockholm\nMalmo")
      .setListFont(&lv_font_montserrat_26)
      .setFont(&lv_font_montserrat_26)
      .addEventCallback(Settings::change_city,
                        lv_event_code_t::LV_EVENT_VALUE_CHANGED, this)
      .setGridCell(2, 1)
      .setWidth(270);
}

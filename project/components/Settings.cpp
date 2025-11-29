#include "Settings.h"
#include "constants.h"
#include "initGUI.h"
#include <lvgl.h>



void city_cancel_cb(lv_event_t * event) {



    gui.closePopup();


}


void city_picker_cb(lv_event_t * event) {


    gui.openPopup().addDropdown().setOptions("Placeholder");


}

void city_dropdown_cb(lv_event_t * event) {

    lv_obj_t* dropdown = (lv_obj_t*)lv_event_get_target(event);

    int selected = lv_dropdown_get_selected(dropdown);

    int len = lv_dropdown_get_option_count(dropdown);

    if(selected == len-1) {
        //gui.openPopup().addTitle("Add new city...").addButton("Cancel").addButton("Next").getTile().setSize(550, 200).setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_AROUND).addLabel().setText("Select the first\nletter of your city.").setFont(&lv_font_montserrat_32).getTile().addDropdown().setOptions("A\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ").setListFont(&font_header).setFont(&font_header);
        gui.openPopup()
        .addButton("Cancel", city_cancel_cb).addButton("Next", city_picker_cb).getTile().setSize(550, 200)
        .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_AROUND)
        .addLabel()
        .setText("Add new city...")
        .setFont(&lv_font_montserrat_48)
        .getTile()
        .addLabel()
        .setText("Select the first\nletter of your city.")
        .setFont(&lv_font_montserrat_32).getTile().addDropdown().setOptions("A\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ").setListFont(&lv_font_montserrat_48).setFont(&lv_font_montserrat_48);
    }
}


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

void Settings::process() {}

void Settings::constructUI(Tile* gui) {
  Tile& settings_tile = *gui;

  // Heading
  settings_tile.setGridLayout(columns, row)
      .addLabel()
      .setText("Settings")
      .setFont(&lv_font_montserrat_48)
      .setGridCell(0, 0, 1, 2);

  settings_tile.addLabel()
      .setText("Weather parameter:")
      .setFont(&lv_font_montserrat_32)
      .setGridCell(1, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);

  settings_tile.addDropdown()
      .setOptions("Temperature\nMoisture\nWind")
      .setListFont(&lv_font_montserrat_32)
      .setFont(&lv_font_montserrat_32)
      .addEventCallback(Settings::change_weather_parameter,
                        lv_event_code_t::LV_EVENT_VALUE_CHANGED, this)
      .setGridCell(1, 1)
      .setWidth(270);

  settings_tile.addLabel("Select option 2 ")
      .setText("Weather location:")
      .setFont(&lv_font_montserrat_32)
      .setGridCell(2, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);

  settings_tile.addDropdown()
      .setOptions("Karlskrona\nGothenburg\nStockholm\nMalmo")
      .setListFont(&lv_font_montserrat_32)
      .setFont(&lv_font_montserrat_32)
      .addEventCallback(Settings::change_city,
                        lv_event_code_t::LV_EVENT_VALUE_CHANGED, this)
      .setGridCell(2, 1)
      .setWidth(270);
}

#include "Settings.h"
#include "constants.h"
#include "../prelude.h"
#include "apiLogic/ApiHandling.h"
#include "../gui/Button.h"
#include "../FileHandling.h"
#ifdef LILYGO_BUILD
#include <Arduino.h>
#else
#ifdef NATIVE_BUILD
#include "nativeReplacements/String.h"
#endif

#endif
#include <lvgl.h>
#include <ArduinoJson.h>
#include <iostream>



void city_cancel_cb(lv_event_t * event) {
    getGui().closePopup();
}
void Settings::city_confirm_cb(lv_event_t * event) {
    char filtering_text[100]; 
    Settings* old_dropdown = (Settings*)lv_event_get_user_data(event);
    lv_dropdown_get_selected_str(getGui().openPopup().getDropdown("cities").getWidgetPtr(), filtering_text, 100);
    getGui().closePopup();
    std::string city = std::string(filtering_text);
    
    for(auto& check: old_dropdown->available_cities) {
        if(check == city) {
            return;
        }
    }
    old_dropdown->available_cities.push_back(city);

    old_dropdown->city = city;
    getForecastScreen().refresh();
    
    old_dropdown->ui_tile->getDropdown("cities").setOptions(old_dropdown->available_cities)
            .pushOption("add location...");
            

}
std::string Settings::getSelectedCity() {
    return this->city;
}
WeatherParameter Settings::getSelectedParameter() {
    return this->weather_parameter;
}
void Settings::city_picker_cb(lv_event_t * event) {
    char filtering_text[2]; 
    Settings* old_dropdown = (Settings*)lv_event_get_user_data(event);
    lv_dropdown_get_selected_str(getGui().openPopup().getDropdown("letters").getWidgetPtr(), filtering_text, 2);
    Popup& popup = getGui().switchPopup();
    
    Dropdown& dropdown = popup.getTile().setSize(550, 200)
        .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY)
        .addLabel()
        .setText("Add new location...")
        .setFont(&font_header)
        .getTile()
        .addLabel()
        .setText("Select the location\nyou'd like to add.")
        .setFont(&font_regular).setTextAlign(LV_TEXT_ALIGN_CENTER).getTile().addDropdown("cities");

    dropdown.setOptions("").setListFont(&font_regular).setFont(&font_regular).setWidth(300);
    int option_counter = 0;
    APIhandler handler;

   std::unordered_map<std::string, StationObject> placeholder_cities_list = handler.getStationsArray(1);
    std::vector<std::string> cities = {};
    for(auto &city : placeholder_cities_list) {
        if(city.first.at(0) == filtering_text[0]) {
            cities.push_back(city.first);
            option_counter++;
        }
    }
    std::sort(cities.begin(), cities.end());
    dropdown.setOptions(cities);
    
    if(option_counter > 0) {
        popup.addButton("Cancel", city_cancel_cb).addButton("Finish", city_confirm_cb, old_dropdown);
    } else {
        getGui().switchPopup().addButton("Okay", city_cancel_cb).getTile().setSize(550, 200)
        .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_AROUND)
        .addLabel()
        .setText("Add new location...")
        .setFont(&font_header)
        .getTile()
        .addLabel()
        .setText("There were no locations\nbeginning with this letter\n\n")
        .setFont(&lv_font_montserrat_32).setTextAlign(LV_TEXT_ALIGN_CENTER);
    }
    
}
void Settings::city_dropdown_cb(lv_event_t * event) {
    lv_obj_t* dropdown = (lv_obj_t*)lv_event_get_target(event);
    Settings* settings = (Settings*)lv_event_get_user_data(event);
    int selected = lv_dropdown_get_selected(dropdown);
    int len = lv_dropdown_get_option_count(dropdown);
    if(selected == len-1) {
        Popup& popup = getGui().openPopup();
        popup.getTile().setSize(550, 200)
        .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_AROUND)
        .addLabel()
        .setText("Add new location...")
        .setFont(&font_header)
        .getTile()
        .addLabel()
        .setText("Select the first\nletter of your location.")
        .setFont(&lv_font_montserrat_32).setTextAlign(LV_TEXT_ALIGN_CENTER);
        Dropdown& dropdown = popup.getTile().addDropdown("letters");
        dropdown.setOptions("A\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ\nÅ\nÄ\nÖ").setListFont(&font_header).setFont(&font_header);
        
        popup.addButton("Cancel", city_cancel_cb).addButton("Next", Settings::city_picker_cb, settings);
    } else {
      settings->city = settings->available_cities.at(selected);
      getForecastScreen().refresh();
    }
}

void Settings::set_default(lv_event_t* event) {
    FileHandler handler; 
    handler.listDir(LittleFS, "/", 1);
    lv_obj_t* button = (lv_obj_t*)lv_event_get_target(event);
    Settings* classData = (Settings*)lv_event_get_user_data(event);
    lv_obj_t* parent = lv_obj_get_parent(button);

    //WidgetContainer* parrent = (WidgetContainer*)(lv_obj_get_parent(button));
    JsonDocument doc;
    
    for(string value : classData->available_cities)
        doc["cities"].add(value);

    if(!classData->city.empty())
        doc["selectedCity"] = classData->city;
    else 
        doc["selectedCity"] = "Karlskrona";
    int parameter = static_cast<int>(classData->weather_parameter);
    doc["parameter"] = parameter;

    String data = "";
    serializeJsonPretty(doc, data);

    std::cout << data <<std::endl;
    handler.writeFile(LittleFS, "/defaultSettings.json", data.c_str());

    String info = handler.readFile(LittleFS, "/defaultSettings.json");
    std::cout << info << std::endl;
  
}


void Settings::reset_defaults(lv_event_t * event) {
    FileHandler handler;
    lv_obj_t* button = (lv_obj_t*)lv_event_get_target(event);
    Settings* classData = (Settings*)lv_event_get_user_data(event);

    const char* filename = "/defaultSettings.json";
    LittleFS.begin();

    if (!LittleFS.exists(filename)) {
        std::cout << "[Settings] settings file did not exist!" << std::endl;
        classData->weather_parameter = WeatherParameter::Humidity;
        classData->available_cities = {"Karlskrona"};
        classData->city = "Karlskrona";
    } else {
        JsonDocument doc;
        String jsonString = handler.readFile(LittleFS, filename);
        if (deserializeJson(doc, jsonString) != DeserializationError::Ok) {
            classData->weather_parameter = WeatherParameter::Humidity;
            classData->available_cities = {"Karlskrona"};
            classData->city = "Karlskrona";
        } else {
            classData->weather_parameter = static_cast<WeatherParameter>(doc["parameter"].as<int>());
            classData->available_cities.clear();
            const JsonArray& arr = doc["cities"];

            for (const JsonVariant& v : arr) {
                classData->available_cities.push_back(v);
            }
            if (classData->available_cities.empty()) {
                classData->available_cities = {"Karlskrona"};
            }

            if (!doc["selectedCity"].isNull()) {
                classData->city = std::string(doc["selectedCity"]);
            } else {
                classData->city = "Karlskrona";
            }
            
        }
        std::cout << "[Settings] settings file loaded" << std::endl;
    }
}

Settings::Settings() {
    FileHandler handler; 
    const char* filename = "/defaultSettings.json";
    LittleFS.begin();

    if(!LittleFS.exists(filename)) {

        weather_parameter = WeatherParameter::Humidity;
        available_cities = {"Karlskrona"};
        city = "Karlskrona";
    }
    else{
        
        JsonDocument doc;
        String jsonString = handler.readFile(LittleFS, filename);
        //std::cout << jsonString << std::endl;
        deserializeJson(doc, jsonString);

        weather_parameter = static_cast<WeatherParameter>(doc["parameter"].as<int>());
        JsonArray availableArrayJson;
        if(!doc["selectedCity"].isNull()){
            city = string(doc["selectedCity"].as<const char*>());
            availableArrayJson = doc["cities"].as<JsonArray>();
            if(!availableArrayJson.isNull())
            for(JsonVariant value : availableArrayJson)
                available_cities.push_back(string(value.as<const char*>()));
        }
        else {
            available_cities = {"Karlskrona"};
            city = "Karlskrona";
        }
    }
}

Settings::~Settings() {} 

// WARNING: Index of weather parameters must preserve order
void Settings::change_weather_parameter(lv_event_t* event) {
  void* dropdown = lv_event_get_target(event);
  uint32_t index = lv_dropdown_get_selected((lv_obj_t*)dropdown);
  WeatherParameter param;
  switch(index) {
        case 0:
          param = WeatherParameter::Temperature;
        break;
        case 1:
          param = WeatherParameter::WindSpeed;
        break;
        case 2:
          param = WeatherParameter::Humidity;
        break;
        case 3:
          param = WeatherParameter::Rainfall;
        break;
        case 4:
          param = WeatherParameter::AirPressure;
        break;
    }
  auto settings = (Settings*)lv_event_get_user_data(event);
  settings->weather_parameter = param;
  getForecastScreen().refreshWeatherParameter();
  getWeatherChartScreen().reset();
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

int Settings::getCurrentCityIndex(){
    int index = 0;
    for(string value : available_cities)
    {
        if(value == city)
            return index;
        index++;
    }
    return 0;
}

void Settings::constructUI(Tile* gui) {
    static int32_t columns[] = {200, 400, LV_GRID_TEMPLATE_LAST};
    static int32_t row[] = {110, 80, 80, 80, LV_GRID_TEMPLATE_LAST};

    ui_tile = gui;
  //Tile& settings_tile = *gui;
    gui->setGridLayout(columns, row)
    .addLabel().setText("Settings").setFont(&lv_font_montserrat_48)
    .setGridCell(0, 0, 1, 2).getTile()
    .addLabel().setText("Parameter:").setFont(&font_regular)
    .setGridCell(1, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END).getTile()
    .addDropdown().setOptions("Temperature\nWind Speed\nHumidity\nRainfall\nAir Pressure").setSelectedOption(static_cast<int>(this->weather_parameter)).setListFont(&font_regular).setFont(&font_regular)
    .addEventCallback(Settings::change_weather_parameter, lv_event_code_t::LV_EVENT_VALUE_CHANGED, this)
    .setGridCell(1, 1).setWidth(370).getTile()
    .addLabel("Select option 2 ").setText("Location:").setFont(&font_regular)
    .setGridCell(2, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END).getTile()
    .addDropdown("cities")
    .setOptions(available_cities)
    .setSelectedOption(this->getCurrentCityIndex())
    .pushOption("add location...")
    .setListFont(&font_regular)
    .setFont(&font_regular)
    .addEventCallback(city_dropdown_cb, LV_EVENT_VALUE_CHANGED, this)
    .setGridCell(2, 1).setWidth(370).getTile()
    .addButton("Set Default")
    .setBtnText("Set Default")
    .setGridCell(3, 0, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END)
    .addEventCallback(set_default, LV_EVENT_CLICKED, this)
    .getTile()
    .addButton("Reset Defaults")
    .setBtnText("Reset Defaults")
    .setGridCell(3, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START)
    .addEventCallback(reset_defaults, LV_EVENT_CLICKED, this);


            /*

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
    */
}

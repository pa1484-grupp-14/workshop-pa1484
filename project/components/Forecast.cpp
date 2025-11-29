#include "Forecast.h"
#include "utilities.h"
#include "../prelude.h"

#include "gui/icons/wi_celsius.c"
#include "gui/icons/wi_cloudy.c"
#include "gui/icons/wi_raindrop.c"

#include "gui/icons/wi_day_cloudy.c"
#include "gui/icons/wi_day_fog.c"
#include "gui/icons/wi_day_rain.c"
#include "gui/icons/wi_day_showers.c"
#include "gui/icons/wi_day_sleet.c"
#include "gui/icons/wi_day_snow.c"
#include "gui/icons/wi_day_sprinkle.c"
#include "gui/icons/wi_day_sunny.c"
#include "gui/icons/wi_day_sunny_overcast.c"
#include "gui/icons/wi_day_thunderstorm.c"

//Symbol Codes as defined by SMHI API
#define SC_CLEAR_SKY 1
#define SC_NEARLY_CLEAR_SKY 2
#define SC_VARIABLE_CLOUDS 3
#define SC_HALFCLEAR_SKY 4
#define SC_CLOUDY_SKY 5
#define SC_OVERCAST 6
#define SC_FOG 7
#define SC_LIGHT_RAIN_SHOWERS 8
#define SC_MODERATE_RAIN_SHOWERS 9
#define SC_HEAVY_RAIN_SHOWERS 10
#define SC_THUNDERSTORM_SHOWERS 11
#define SC_LIGHT_SLEET_SHOWERS 12
#define SC_MODERATE_SLEET_SHOWERS 13
#define SC_HEAVY_SLEET_SHOWERS 14
#define SC_LIGHT_SNOW_SHOWERS 15
#define SC_MODERATE_SNOW_SHOWERS 16
#define SC_HEAVY_SNOW_SHOWERS 17
#define SC_LIGHT_RAIN 18
#define SC_MODERATE_RAIN 19
#define SC_HEAVY_RAIN 20
#define SC_THUNDER 21
#define SC_LIGHT_SLEET 22
#define SC_MODERATE_SLEET 23
#define SC_HEAVY_SLEET 24
#define SC_LIGHT_SNOW 25
#define SC_MODERATE_SNOW 26
#define SC_HEAVY_SNOW 27

WidgetContainer& AddForecastDay(WidgetContainer& tile, const std::string& day,
                                const std::string& date, int temp, int moisture,
                                int icon) {
  static int cols[] = {100, 90, 90, 100, 80, LV_GRID_TEMPLATE_LAST};
  static int rows[] = {35, 40, LV_GRID_TEMPLATE_LAST};
  const lv_image_dsc_t* icon_image = &wi_day_sunny;

  switch (icon) {
    case SC_CLEAR_SKY:
      icon_image = &wi_day_sunny;
      break;
    case SC_NEARLY_CLEAR_SKY:
      icon_image = &wi_day_sunny;
      break;
    case SC_VARIABLE_CLOUDS:
      icon_image = &wi_day_sunny_overcast;
      break;
    case SC_HALFCLEAR_SKY:
      icon_image = &wi_day_cloudy;
      break;
    case SC_CLOUDY_SKY:
      icon_image = &wi_cloudy;
      break;
    case SC_OVERCAST:
      icon_image = &wi_day_sunny_overcast;
      break;
    case SC_FOG:
      icon_image = &wi_day_fog;
      break;
    case SC_LIGHT_RAIN_SHOWERS:
      icon_image = &wi_day_sprinkle;
      break;
    case SC_MODERATE_RAIN_SHOWERS:
      icon_image = &wi_day_showers;
      break;
    case SC_HEAVY_RAIN_SHOWERS:
      icon_image = &wi_day_rain;
      break;
    case SC_THUNDERSTORM_SHOWERS:
      icon_image = &wi_day_thunderstorm;
      break;
    case SC_LIGHT_SLEET_SHOWERS:
      icon_image = &wi_day_sprinkle;
      break;
    case SC_MODERATE_SLEET_SHOWERS:
      icon_image = &wi_day_showers;
      break;
    case SC_HEAVY_SLEET_SHOWERS:
      icon_image = &wi_day_sleet;
      break;
    case SC_LIGHT_SNOW_SHOWERS:
      icon_image = &wi_day_sprinkle;
      break;
    case SC_MODERATE_SNOW_SHOWERS:
      icon_image = &wi_day_snow;
      break;
    case SC_HEAVY_SNOW_SHOWERS:
      icon_image = &wi_day_snow;
      break;
    case SC_LIGHT_RAIN:
      icon_image = &wi_day_sprinkle;
      break;
    case SC_MODERATE_RAIN:
      icon_image = &wi_day_showers;
      break;
    case SC_HEAVY_RAIN:
      icon_image = &wi_day_rain;
      break;
    case SC_THUNDER:
      icon_image = &wi_day_thunderstorm;
      break;
    case SC_LIGHT_SLEET:
      icon_image = &wi_day_sprinkle;
      break;
    case SC_MODERATE_SLEET:
      icon_image = &wi_day_showers;
      break;
    case SC_HEAVY_SLEET:
      icon_image = &wi_day_sleet;
      break;
    case SC_LIGHT_SNOW:
      icon_image = &wi_day_sprinkle;
      break;
    case SC_MODERATE_SNOW:
      icon_image = &wi_day_snow;
      break;
    case SC_HEAVY_SNOW:
      icon_image = &wi_day_snow;
      break;
    default:
      icon_image = &wi_cloudy;
      break;
  }

  auto container = tile.addContainer();
  container.setGridLayout(cols, rows).setSize(550, 125);
  container.addImage()
      .setSource(icon_image)
      .setGridCell(0, 0, 2, 1)
      .setSize(100, 80);
  container.addLabel()
      .setText(day)
      .setFont(&lv_font_montserrat_48)
      .setGridCell(0, 1, 1, 3);
  container.addLabel()
      .setText(date)
      .setFont(&lv_font_montserrat_24)
      .setGridCell(0, 4)
      .setSize(100, 40);
  container.addLabel()
      .setText(std::to_string(temp))
      .setFont(&lv_font_montserrat_24)
      .setGridCell(1, 1, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
  container.addImage()
      .setSource(&wi_celsius)
      .setGridCell(1, 2, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);
  container.addLabel()
      .setText(std::to_string(moisture) + "%")
      .setFont(&lv_font_montserrat_32)
      .setGridCell(1, 3, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
  container.addImage()
      .setSource(&wi_raindrop)
      .setGridCell(1, 4, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);

  return tile;
}


// NOTICE: modified from https://www.geeksforgeeks.org/dsa/find-day-of-the-week-for-a-given-date/ (retrieved 20/11/2025)
// Function to calculate the day of the week using the formula-based approach
int dayOfWeek(int d, int m, int y) {
  // Predefined month codes for each month
  // As each month is not an integer ammount of weeks long, it needs to be offset by this many days to account for carryover into the next month.
  static int monthCode[] = {5, 1, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3};

  // Adjust year for January and February
  if (m < 3) {
    y -=
        1;  // If month is January or February, treat them as part of the previous year
  }

  // Calculate the year code
  int yearCode = (y % 100) + (y % 100) / 4;

  // Adjust year code for the century
  yearCode = (yearCode + (y / 100) / 4 + 5 * (y / 100)) % 7;

  // Calculate the day of the week and return the value as an integer
  return (d + monthCode[m - 1] + yearCode) % 7;
}



Forecast::Forecast() {}
Forecast::~Forecast() {}

void Forecast::constructUI(Tile* tile) {

    ui_tile = tile;
    Widget& spinner = tile->addSpinner().center();
    spinner.setSize(60,60);
    tile->addLabel().setText("Waiting for wifi...").setFont(&lv_font_montserrat_32).alignTo(spinner, LV_ALIGN_BOTTOM_MID, 0, 50);
  status = ForecastStatus::WaitingForWifi;
    

}
void Forecast::reset() {
  if(ui_tile == nullptr) {
    Serial.println("FORECAST TILE IS NULL!");
  } else {

    ui_tile->clear();
    Widget& spinner = ui_tile->addSpinner().center();
      spinner.setSize(60,60);
      ui_tile->addLabel().setText("Waiting for wifi...").setFont(&lv_font_montserrat_32).alignTo(spinner, LV_ALIGN_BOTTOM_MID, 0, 50);
    status = ForecastStatus::WaitingForWifi;
    
  } 
}
void construct_forecast_ui(Tile* tile, std::vector<ForecastObject> forecasts) {
  tile->clear();
  Container& weather_forecast = tile->addContainer().disableFrame();
  weather_forecast.setSize(600, 1000).setFlexLayout(LV_FLEX_FLOW_COLUMN,
                                                    LV_FLEX_ALIGN_SPACE_EVENLY);

  for (size_t i = 0; i < 7; i++) {
    ForecastObject& day = forecasts.at(i);
    int year = std::stoi(day.time.substr(0, 4));
    int month = std::stoi(day.time.substr(5, 2));
    int d = std::stoi(day.time.substr(8, 2));
    std::string day_string;
    switch (dayOfWeek(d, month, year)) {
      case 0:
        day_string = "Monday";
        break;
      case 1:
        day_string = "Tuesday";
        break;
      case 2:
        day_string = "Wednesday";
        break;
      case 3:
        day_string = "Thursday";
        break;
      case 4:
        day_string = "Friday";
        break;
      case 5:
        day_string = "Saturday";
        break;
      case 6:
        day_string = "Sunday";
        break;

      default:
        day_string = "null";
        break;
    }

    AddForecastDay(
        weather_forecast, day_string,
        "(" + day.time.substr(5, 2) + "/" + day.time.substr(8, 2) + ")",
        day.air_temperature, day.relative_humidity, day.symbol_code);
  }
}
void Forecast::switchToForecastScreen(std::vector<ForecastObject>& forecasts) {
    ui_tile->clear();
    construct_forecast_ui(ui_tile, forecasts);
    status = ForecastStatus::Fetched;
}
void Forecast::switchToLoadingScreen() {
    status = ForecastStatus::Fetching;
    ui_tile->clear();
    ui_tile->addLabel().setText("Fetching Forecast...\n(Please remain patient)").setFont(&lv_font_montserrat_48).center();
}
void Forecast::process() {
    if(status == ForecastStatus::WaitingForWifi) {
      if(is_wifi_connected()) {
        this->switchToLoadingScreen();
      }
    } else if (status == ForecastStatus::Fetching) {
      if(true) {

      APIhandler handler;

      std::unordered_map<std::string, StationObject> stationsArray = handler.getStationsArray(1);
      
      if(stationsArray.size() < 1) {
        ui_tile->clear();
        ui_tile->addLabel().setText("Failed fetching available weather stations.").center();
        status == ForecastStatus::FailedFetch;
      }
      try {
        Serial.print("Beginning fetch of city: ");
        std::string selected_city = getSettingsScreen().getSelectedCity();
        Serial.println(selected_city.c_str());
        Serial.print("banan");
      StationObject station =
      handler.getStationFromArray(stationsArray, selected_city); 
        //Serial.println("name: " + String(station.getName().c_str()) + " longitude: " + String(station.getLon()) + " latitude: " + String(station.getLat()));
      std::vector<ForecastObject> forecasts = handler.getForecastNext7Days(station);
        this->switchToForecastScreen(forecasts);
      } catch(int err) {
        ui_tile->clear();
        ui_tile->addLabel().setText("Failed fetching forecast data.").center();
        status == ForecastStatus::FailedFetch;
        Serial.println("Failed fetching forecast data.");
      }
      }
      
    }
}

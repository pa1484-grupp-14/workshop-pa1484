#include "Forecast.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "prelude.h"

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

void forecast_great_success(std::vector<ForecastObject>& forecasts) {
  getForecastScreen().switchToForecastScreen(forecasts);
}
void forecast_success(
    std::unordered_map<std::string, StationObject>& stationArray) {
  getForecastScreen().switchToLoadingForecasts(stationArray);
}
void forecast_epic_fail() {
  getForecastScreen().switchToFailScreen();
}
void forecast_refresh_pls(lv_event_t* _e) {
  getForecastScreen().refresh();
}
void createLoadingUi(Tile* ui_tile, std::string statusText) {
  ui_tile->clear();
  Widget& label = ui_tile->addLabel().setText(statusText);
  Widget& spinner = ui_tile->addSpinner();
  spinner.center().setSize(60, 60);
  label.setFont(&lv_font_montserrat_32)
      .alignTo(spinner, LV_ALIGN_BOTTOM_MID, 0, 50);
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

WidgetContainer& AddForecastDay(WidgetContainer& tile, const std::string& day,
                                const std::string& date,
                                ForecastObject forecast) {
  static int cols[] = {100, 90, 90, 100, 80, LV_GRID_TEMPLATE_LAST};
  static int rows[] = {35, 32, 32, LV_GRID_TEMPLATE_LAST};
  const lv_image_dsc_t* icon_image = &wi_day_sunny;

  switch (forecast.symbol_code) {
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
  container.setGridLayout(cols, rows).setSize(550, 160);
  container.addImage()
      .setSource(icon_image)
      .setGridCell(0, 0, 3, 1)
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

  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << forecast.air_temperature;
    std::string s = stream.str();
    container.addLabel()
        .setText(s)
        .setFont(&lv_font_montserrat_32)
        .setGridCell(1, 3, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
    container.addImage()
        .setSource(&wi_celsius)
        .setGridCell(1, 4, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);
    container.addLabel()
        .setText(std::to_string(forecast.probability_of_precipitation) + "%")
        .setFont(&lv_font_montserrat_32)
        .setGridCell(2, 3, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
    container.addImage()
        .setSource(&wi_raindrop)
        .setGridCell(2, 4, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);
  }
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << forecast.wind_speed
           << "m/s";
    std::string s = stream.str();
    container.addLabel()
        .setText(s)
        .setFont(&lv_font_montserrat_32)
        .setGridCell(1, 1, 1, 2, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
  }
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1)
           << forecast.precipitation_amount_mean << "mm";
    std::string s = stream.str();
    container.addLabel()
        .setText(s)
        .setFont(&lv_font_montserrat_32)
        .setGridCell(2, 1, 1, 2, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
  }

  return tile;
}

Forecast::Forecast() {}
Forecast::~Forecast() {}

void Forecast::constructUI(Tile* tile) {
  uiTile = tile;
  refresh();
}
void Forecast::refresh() {
  if (uiTile) {
    createLoadingUi(uiTile, "Waiting for wifi...");
    status = ForecastStatus::WaitingForWifi;
  } else {
    std::cout << "[Forecast::reset]: ui_tile is a nullptr!";
  }
}

void Forecast::refreshWeatherParameter() {
  const char* days[] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                        "Friday", "Saturday", "Sunday"};
  if (status == ForecastStatus::Fetched) {
    //Create UI container
    uiTile->clear();
    Container& container = uiTile->addContainer().disableFrame();
    container.setSize(600, 1300).setFlexLayout(LV_FLEX_FLOW_COLUMN,
                                               LV_FLEX_ALIGN_SPACE_EVENLY);

    container.addLabel()
        .setText(currentCity + "'s forecast:")
        .setFont(&font_header);

    for (auto& sample : forecastData) {
      //format day and dare strings
      std::string date_string =
          "(" + sample.time.substr(5, 2) + "/" + sample.time.substr(8, 2) + ")";
      std::string day_string;

      int year = std::stoi(sample.time.substr(0, 4));
      int month = std::stoi(sample.time.substr(5, 2));
      int day = std::stoi(sample.time.substr(8, 2));
      int weekday = dayOfWeek(day, month, year);

      if (weekday < 7) {
        day_string = days[weekday];
      } else {
        day_string = "null day";
      }

      //Add day to the UI
      AddForecastDay(container, day_string, date_string, sample);
    }
  }
}

void Forecast::switchToForecastScreen(std::vector<ForecastObject>& forecasts) {
  if (forecasts.size() < 7) {
    switchToFailScreen();
  } else {
    std::cout << "[construct_forecast_ui]: we have " << forecasts.size()
              << " forecast days" << std::endl;
    for (size_t i = 0; i < 7; i++) {

      ForecastObject& day = forecasts.at(i);
      forecastData[i] = day;
    }
    status = ForecastStatus::Fetched;
    refreshWeatherParameter();
  }
}
void Forecast::switchToLoadingForecasts(
    std::unordered_map<std::string, StationObject>& stationsArray) {
  if (stationsArray.size() < 1) {
    switchToFailScreen();
    return;
  }
  try {
    APIhandler handler;
    currentCity = getSettingsScreen().getSelectedCity();
    std::cout << "[ForecastScreen]: Beginning fetch of city: "
              << currentCity.c_str() << std::endl;
    StationObject station =
        handler.getStationFromArray(stationsArray, currentCity);
    handler.getForecastNext7DaysAsync(station, forecast_great_success,
                                      forecast_epic_fail);
    createLoadingUi(uiTile, "Fetching Forecast...");
    status = ForecastStatus::FetchingForecast;
  } catch (int err) {
    uiTile->clear();
    uiTile->addLabel().setText("Failed fetching forecast data.").center();
    std::cout << "[ForecastScreen]: Failed fetching forecast data."
              << std::endl;
    switchToFailScreen();
  }
}
void Forecast::switchToFailScreen() {
  uiTile->clear();
  Widget& label = uiTile->addLabel().setText("An error has occured.").center();
  uiTile->addButton("okay")
      .setBtnText("refresh")
      .addEventCallback(forecast_refresh_pls, LV_EVENT_CLICKED)
      .alignTo(label, LV_ALIGN_BOTTOM_MID, 0, 100);
  status == ForecastStatus::FailedFetch;
}
void Forecast::switchToLoadingStations() {
  status = ForecastStatus::FetchingStations;
  createLoadingUi(uiTile, "Finding weather stations...");
  APIhandler handler;
  handler.getStationsArrayAsync(1, forecast_success, forecast_epic_fail);
}
void Forecast::process() {
  if (status == ForecastStatus::WaitingForWifi) {
    if (is_wifi_connected()) {
      this->switchToLoadingStations();
    }
  }
}

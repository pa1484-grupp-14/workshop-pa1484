#include "WeatherChart.h"
#include "apiLogic/ApiHandling.h"
#include "prelude.h"
#include <iostream>
WeatherChart::WeatherChart() {}
WeatherChart::~WeatherChart() {}
void createChartUi(Tile* tile) {
    std::cout << "[WeatherChart] trying to fetch historical data..." << std::endl;
    APIhandler handler;
    auto stations = handler.getStationsArray(1);
    std::string city = getSettingsScreen().getSelectedCity();
    auto station = handler.getStationFromArray(stations, city);
    auto data_points = handler.getHistoricalData(station, 1);   
    std::cout << "[WeatherChart] fetched " << data_points.size() << " data points." << std::endl;
    std::vector<int32_t> data = std::vector<int32_t>{20, 40, 30, 50, 60, 5, 10, 99, 80, 0};
    for (size_t i = 0; i < 10; i++)
    {
      data[i] = (int32_t)data_points[i].getValue();
    }
      
    
    tile->
      clear();
    tile->setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY)
      .addLabel()
      .setText("Weather chart")
      .setFont(&lv_font_montserrat_48)
      .getTile()
      .addChart()
      .addSeries("main series")
      .addPoints("main series", data)
      .setSize(500, 300);
}
void WeatherChart::process() {
    if(status == WeatherChartStatus::WaitingForWiFi) {
      if(is_wifi_connected()) {
        status = WeatherChartStatus::FetchingHistoricalData;
        createLoadingUi(ui_tile, "Fetching historical data...");
      }
    } else if (status == WeatherChartStatus::FetchingHistoricalData) {
      createChartUi(ui_tile);
      status = WeatherChartStatus::FetchedHistory;
    }
}
void WeatherChart::constructUI(Tile* tile) {
  ui_tile = tile;
  createLoadingUi(tile, "Waiting for wifi...");
}

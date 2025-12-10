#include "WeatherChart.h"
#include "apiLogic/ApiHandling.h"
#include "prelude.h"
#include <iostream>



static char** currentScaleNames = nullptr;
static int currentScaleNameCount = 10;

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
    std::vector<int32_t> data = std::vector<int32_t>(data_points.size());
    for (size_t i = 0; i < data_points.size(); i++)
    {
        data[i] = (int32_t)data_points[i].getValue();
    }
    if(currentScaleNames != nullptr) {
        for (size_t i = 0; i < currentScaleNameCount; i++)
        {
            delete currentScaleNames[i];
        }
        delete[] currentScaleNames;
        currentScaleNames = nullptr;
    }
    currentScaleNames = new char*[currentScaleNameCount+1];
    currentScaleNames[currentScaleNameCount] = nullptr;
    int in = data_points.size() - 1;
    for (size_t i = 0; i < currentScaleNameCount; i++)
    {
      int a = in * i / (currentScaleNameCount-1);
      const std::string& this_entry = data_points[a].getDate().substr(5,5);
      currentScaleNames[i] = new char[this_entry.size()+1];
      for (size_t j = 0; j < this_entry.size(); j++)
      {
        currentScaleNames[i][j] = this_entry[j];
      }
      currentScaleNames[i][this_entry.size()] = 0;
    }
      
    
    tile->
      clear();
    auto& container = tile->addLabel()
      .setText("Weather chart")
      .setFont(&lv_font_montserrat_48)
      .getTile().setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY).addContainer().disableFrame().setSize(580, 370);
    auto& chart = container
      .addChart()
      .addSeries("main series")
      .addPoints("main series", data)
      .setSize(1500, 300);

    lv_obj_t* scale_bottom = lv_scale_create(container.getWidgetPtr());
    lv_scale_set_mode(scale_bottom, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_obj_set_size(scale_bottom, 1500, 25);
    lv_scale_set_total_tick_count(scale_bottom, currentScaleNameCount);
    lv_scale_set_major_tick_every(scale_bottom, 1);
    lv_obj_set_style_pad_hor(scale_bottom, lv_chart_get_first_point_center_offset(chart.getWidgetPtr()), 0);
    lv_obj_set_y(scale_bottom, 300);
    lv_scale_set_text_src(scale_bottom, (const char**)(currentScaleNames));
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

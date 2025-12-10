#include "WeatherChart.h"
#include "apiLogic/ApiHandling.h"
#include "prelude.h"
#include <iostream>
#include <ctime>



static char** currentScaleNames = nullptr;
static int currentScaleNameCount = 10;

WeatherChart::WeatherChart() {}
WeatherChart::~WeatherChart() {}


static void slider_scroll_cb(lv_event_t * e)
{
    lv_obj_t * slider = (lv_obj_t*)lv_event_get_target(e);
    int precentage = lv_slider_get_value(slider);
    int scroll = precentage * 10;
    lv_obj_t * container = (lv_obj_t*)lv_event_get_user_data(e);
    lv_obj_scroll_to(container, scroll, 0, LV_ANIM_OFF);
}
void createChartUi(Tile* tile) {
    WeatherParameter parameter = getSettingsScreen().getSelectedParameter();
    std::cout << "[WeatherChart] trying to fetch historical data..." << std::endl;
    APIhandler handler;
    auto stations = handler.getStationsArray(1);
    std::string city = getSettingsScreen().getSelectedCity();
    auto station = handler.getStationFromArray(stations, city);
    auto data_points = handler.getHistoricalData(station, parameter);   
    std::cout << "[WeatherChart] fetched " << data_points.size() << " data points." << std::endl;
    std::vector<int32_t> data = std::vector<int32_t>(data_points.size());
    int min = 100000;
    int max = -100000;
    for (size_t i = 0; i < data_points.size(); i++)
    {
        int value = (int32_t)data_points[i].getValue();
        min = std::min(min, value);
        max = std::max(max, value);
        data[i] = value;
    }
    min -= min % 10 + 10;
    max += 10 - (max % 10);
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
        char buffer[20];
        std::time_t seconds = data_points[a].getDate();
        strftime(buffer, sizeof(buffer), "%b-%d", localtime(&seconds));
        const std::string& this_entry = buffer;
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
      .setFont(&lv_font_montserrat_48).setPos(125, 5)
      .getTile().addContainer().disableFrame().setPos(50,40).setSize(550, 370);
    auto& chart = container
      .addChart()
      .addSeries("main series")
      .addPoints("main series", data)
      .setSize(1500, 300);

    
    lv_obj_set_scrollbar_mode(container.getWidgetPtr(), LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(container.getWidgetPtr(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t* slider = lv_slider_create(tile->getWidgetPtr());
    lv_obj_set_size(slider, 550, 30);
    lv_obj_set_pos(slider, 25, 410);
    lv_chart_set_axis_range(chart.getWidgetPtr(), LV_CHART_AXIS_PRIMARY_Y, min, max);
    lv_chart_set_div_line_count(chart.getWidgetPtr(), (((max-min)/10)+1),currentScaleNameCount);
    lv_obj_t* scale_bottom = lv_scale_create(container.getWidgetPtr());
    lv_obj_t* scale_side = lv_scale_create(tile->getWidgetPtr());
    int offsetting = lv_chart_get_first_point_center_offset(chart.getWidgetPtr());
    lv_scale_set_mode(scale_side, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_mode(scale_bottom, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_obj_set_size(scale_bottom, 1500, 25);
    lv_obj_set_size(scale_side, 25, 300);
    lv_obj_set_pos(scale_side, 25, 59);
    lv_scale_set_range(scale_side, min, max);
    //lv_scale_set_total_tick_count(scale_side, ((max-min)/10)+1);
    lv_scale_set_total_tick_count(scale_bottom, currentScaleNameCount);
    lv_scale_set_major_tick_every(scale_bottom, 1);
    lv_obj_set_style_pad_hor(scale_bottom, offsetting+1, 0);
    lv_obj_set_style_pad_ver(scale_side, offsetting+1, 0);
    lv_obj_set_y(scale_bottom, 300);
    lv_scale_set_text_src(scale_bottom, (const char**)(currentScaleNames));
    lv_scale_set_label_show(scale_side, true);
    lv_obj_add_event_cb(slider, slider_scroll_cb, LV_EVENT_VALUE_CHANGED, (void*)container.getWidgetPtr());
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
void WeatherChart::reset() {
  status = WeatherChartStatus::WaitingForWiFi;
  ui_tile->clear();
  createLoadingUi(ui_tile, "Waiting for wifi...");
}
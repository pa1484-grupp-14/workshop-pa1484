#include "WeatherChart.h"
#include "apiLogic/ApiHandling.h"
#include "prelude.h"
#include <iostream>
#include <ctime>

//"Temporary" storage for the date names along the bottom of the weather chart
static char** currentScaleNames = nullptr;
static int currentScaleNameCount = 10;


WeatherChart::WeatherChart() {}
WeatherChart::~WeatherChart() {}

// This function is called whenever the slider is interacted with
static void slider_scroll_cb(lv_event_t * e)
{
    //Get the slider position
    lv_obj_t * slider = (lv_obj_t*)lv_event_get_target(e);
    int precentage = lv_slider_get_value(slider);
    
    //This was calculated such as that the edges of the weather graph are never seen, but leaves some margin
    int scroll = (precentage * 10) + 40;
    
    //Scroll the chart to the calculated position
    lv_obj_t * container = (lv_obj_t*)lv_event_get_user_data(e);
    lv_obj_scroll_to(container, scroll, 0, LV_ANIM_OFF);
}
//This function is called whenever someone presses the "refresh" button on the error screen of the weather chart
void refreshChart(lv_event_t* _event) {
  getWeatherChartScreen().reset();
    getGui().scrollToTile(2);
}
//Is called whenever the API request for data finishes
void finishedUi(std::vector<HistoricalObject>& data_points) {
  std::cout << "[WeatherChart] fetched " << data_points.size() << " data points." << std::endl;
  getWeatherChartScreen().switchHistoricalUi(data_points);
}
//Is called whenever the API request for data fails
void failedUi() {
  getWeatherChartScreen().switchFailedUi();
}

//Construct the UI for when a failed request occurs
void WeatherChart::switchFailedUi() {
    status = WeatherChartStatus::FetchFail;
    ui_tile->clear();

    auto& label = ui_tile->addLabel()
        .setText("Failed gathering historical data,\nplease check your settings\nand refresh.")
        .setTextAlign(LV_TEXT_ALIGN_CENTER)
        .setFont(&lv_font_montserrat_32)
        .center();

    ui_tile->addButton()
        .setBtnText("Refresh")
        .addEventCallback(refreshChart, LV_EVENT_CLICKED)
        .alignTo(label, LV_ALIGN_CENTER, 0, 100);

    ui_tile->addLabel()
        .setText("Error")
        .setTextAlign(LV_TEXT_ALIGN_CENTER)
        .setFont(&lv_font_montserrat_48)
        .alignTo(label, LV_ALIGN_CENTER, 0, -100);
}

void WeatherChart::switchHistoricalUi(std::vector<HistoricalObject>& data_points) {
    const int PRECISION_LEVEL = 100; 
    status = WeatherChartStatus::FetchedHistory;
    std::vector<int32_t> data = std::vector<int32_t>(data_points.size());
    //create initial height bounds for the chart
    int min = 1000000000;
    int max = -10000000;

    //do we have a unreasonable number of points?
    if(data_points.size() < 10) {
      switchFailedUi();
      return;
    }

    //anaylze every point
    for (size_t i = 0; i < data_points.size(); i++)
    {
        int value = (int32_t)(data_points[i].getValue() * PRECISION_LEVEL);
        min = std::min(min, value);
        max = std::max(max, value);
        data[i] = value;
    }

    //adjust points according to analysis
    min /= PRECISION_LEVEL;
    max /= PRECISION_LEVEL;
    min -= 9;
    min -= min % 10;
    max += 9;
    max -= max % 10;

    //is the range unreasonable? (semi-failed fetches can cause erroneous data points)
    if(max-min >= 10000) {
      switchFailedUi();
      return;
    }

    //construct date names for various data points in a format LVGL understands, starting with deleting old ones
    if(currentScaleNames != nullptr) {
        for (size_t i = 0; i < currentScaleNameCount; i++)
        {
            delete currentScaleNames[i];
        }
        delete[] currentScaleNames;
        currentScaleNames = nullptr;
    }

    //allocate a new string list
    currentScaleNames = new char*[currentScaleNameCount+1];
    currentScaleNames[currentScaleNameCount] = nullptr;

    //Copy new names
    int data_len = data_points.size() - 1;
    for (size_t i = 0; i < currentScaleNameCount; i++)
    {
        //find the data point corresponding to the position of this tick
        int entry = data_len * i / (currentScaleNameCount-1);
        
        //construct a date string
        char buffer[20];
        std::time_t seconds = data_points[entry].getDate();
        strftime(buffer, sizeof(buffer), "%b-%d", localtime(&seconds));
        const std::string& date = buffer;
        
        //allocate just enough data for the string
        currentScaleNames[i] = new char[date.size()+1];
        //copy and null terminate it to the list.
        for (size_t j = 0; j < date.size(); j++)
        {
            currentScaleNames[i][j] = date[j];
        }
        currentScaleNames[i][date.size()] = 0;
    }
      
    //create the new ui
    ui_tile->
      clear();

    WidgetContainer& container = ui_tile->addLabel()
      .setText("Weather chart")
      .setFont(&lv_font_montserrat_32).setPos(175, 5)
      .getTile().addContainer().disableFrame().setPos(70,30).setSize(480, 370);
    
    WidgetContainer& chart = container
      .addChart()
      .addSeries("main series")
      .addPoints("main series", data)
      .setSize(1525, 300);

    Label& unit_label = ui_tile->addLabel();
    unit_label.setTextAlign(LV_TEXT_ALIGN_RIGHT).setPos(5, 11).setSize(80, 30);
    
    switch(getSettingsScreen().getSelectedParameter()) {
        case WeatherParameter::AirPressure:
        unit_label.setText("(hPa)");  
        break;
        case WeatherParameter::Humidity:
        unit_label.setText("(%)");  
        break;
        case WeatherParameter::Temperature:
        unit_label.setText("(C°)");  
        break;
        case WeatherParameter::Rainfall:
        unit_label.setText("(mm)");  
        break;
        case WeatherParameter::WindSpeed:
        unit_label.setText("(m/s)");  
        break;
    }

    //CRUTCH: this code was made on the last day of the project, in which case we had not 
    //made wrappers for the neccesary functions. It was decided that doing this part in raw
    //LVGL would be faster than implementing wrappers, and remaining time (which never came)
    //would have been used to clean it up. So it is very ugly at this moment.

    //disable scrolling on the weather chart since it's going to be controller by the slider
    lv_obj_set_scrollbar_mode(container.getWidgetPtr(), LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(container.getWidgetPtr(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_scroll_to(container.getWidgetPtr(), 40, 0, LV_ANIM_OFF);

    //Create the slider
    lv_obj_t* slider = lv_slider_create(ui_tile->getWidgetPtr());
    lv_obj_set_size(slider, 530, 40);
    lv_obj_set_pos(slider, 35, 395);
    

    //style the chart
    lv_chart_set_axis_range(chart.getWidgetPtr(), LV_CHART_AXIS_PRIMARY_Y, min*PRECISION_LEVEL, max*PRECISION_LEVEL);
    lv_chart_set_div_line_count(chart.getWidgetPtr(), (((max-min)/10)+1),currentScaleNameCount);
    lv_obj_set_style_pad_hor(chart.getWidgetPtr(), 70, 0);
    lv_obj_set_style_margin_hor(chart.getWidgetPtr(), 0, 0);
    lv_obj_set_style_pad_ver(chart.getWidgetPtr(), 0, 0);
    lv_obj_set_style_margin_ver(chart.getWidgetPtr(), 0, 0);
    
    //Create chart scales
    lv_obj_t* scale_bottom = lv_scale_create(container.getWidgetPtr());
    lv_obj_t* scale_side = lv_scale_create(ui_tile->getWidgetPtr());
    
    //get the margin between the chart edge and first data point, used for positioning later.
    int offsetting = lv_chart_get_first_point_center_offset(chart.getWidgetPtr());
    
    //Style and position the scales
    lv_scale_set_mode(scale_side, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_mode(scale_bottom, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_obj_set_size(scale_bottom, 1525, 25);
    lv_obj_set_size(scale_side, 25, 300);
    lv_obj_set_pos(scale_side, 45, 49);
    lv_scale_set_range(scale_side, min, max);
    
    lv_scale_set_total_tick_count(scale_side, ((max-min)/10)+1);
    if(max-min < 200) {
      lv_scale_set_major_tick_every(scale_side, 1);
    } else {
      lv_scale_set_major_tick_every(scale_side, 20);
    }
    
    lv_scale_set_total_tick_count(scale_bottom, currentScaleNameCount);
    lv_scale_set_major_tick_every(scale_bottom, 1);

    lv_obj_set_style_pad_hor(scale_bottom, offsetting+1, 0);
    lv_obj_set_style_margin_hor(scale_bottom, 0, 0);

    lv_obj_set_y(scale_bottom, 299);
    lv_scale_set_text_src(scale_bottom, (const char**)(currentScaleNames));
    lv_scale_set_label_show(scale_side, true);

    //bind the slider to the scrolling of the weather chart
    lv_obj_add_event_cb(slider, slider_scroll_cb, LV_EVENT_VALUE_CHANGED, (void*)container.getWidgetPtr());
}

void WeatherChart::process() {
    if(status == WeatherChartStatus::WaitingForWiFi) {
      if(is_wifi_connected()) {
        status = WeatherChartStatus::FetchingHistoricalData;
        std::cout << "[WeatherChart] trying to fetch historical data..." << std::endl;
        createLoadingUi(ui_tile, "Fetching historical data...");
        
        APIhandler handler;
        auto stations = handler.getStationsArray(1);
        auto station = handler.getStationFromArray(stations, getSettingsScreen().getSelectedCity());
        handler.getHistoricalDataAsync(station, getSettingsScreen().getSelectedParameter(), finishedUi, failedUi);
      }
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
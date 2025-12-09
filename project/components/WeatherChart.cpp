#include "WeatherChart.h"
#include "apiLogic/ApiHandling.h"

WeatherChart::WeatherChart() {}
WeatherChart::~WeatherChart() {}

void WeatherChart::process() {}
void WeatherChart::constructUI(Tile* tile) {
    APIhandler handler;
    //handler.getHistoricalData();   
    tile->
      setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY)
      .addLabel()
      .setText("Weather chart")
      .setFont(&lv_font_montserrat_48)
      .getTile()
      .addChart()
      .addSeries("main series")
      .addPoints("main series", {20, 40, 30, 50, 60, 5, 10, 99, 80, 0})
      .setSize(500, 300);
}
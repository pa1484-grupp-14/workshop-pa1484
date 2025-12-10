#pragma once

#include <lvgl.h>
#include <string>
#include "gui/Gui.h"
#include <vector>
#include "apiLogic/HistoricalObject.h"

enum WeatherChartStatus {
  WaitingForWiFi = 0,
  FetchingHistoricalData,
  FetchedHistory,
  FetchFail,
};

class WeatherChart : public Component {
 private:
 Tile* ui_tile;
 WeatherChartStatus status;
 std::vector<HistoricalObject> samples;
 public:
  WeatherChart();
  ~WeatherChart();
  void constructUI(Tile *gui) override;
  void process() override;
  void reset();
  void switchFetchingUi();
  void switchHistoricalUi(std::vector<HistoricalObject>& data_points);
};

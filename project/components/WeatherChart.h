#pragma once

#include <lvgl.h>
#include <string>
#include "gui/Gui.h"
#include <vector>
#include "apiLogic/HistoricalObject.h"
class WeatherChart : public Component {
 private:
 std::vector<HistoricalObject> samples;
 public:
  WeatherChart();
  ~WeatherChart();
  void constructUI(Tile *gui) override;
  void process() override;
};

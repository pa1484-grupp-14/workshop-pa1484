#pragma once

#include <lvgl.h>
#include <string>
#include "gui/Gui.h"

class WeatherChart : public Component {
 private:
 public:
  WeatherChart();
  ~WeatherChart();
  void constructUI(Tile *gui) override;
  void process() override;
};

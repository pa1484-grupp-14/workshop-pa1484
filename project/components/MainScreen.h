#pragma once

#include <lvgl.h>
#include <string>
#include "gui/Gui.h"

class MainScreen : public Component {
 private:
 public:
  MainScreen();
  ~MainScreen();
  void constructUI(Tile *gui) override;
  void process() override;
};

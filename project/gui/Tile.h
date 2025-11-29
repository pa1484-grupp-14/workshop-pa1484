#ifndef GUI_TILE_H
#define GUI_TILE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class GUI;
#include <lvgl.h>
#include "WidgetContainer.h"

class Tile : public WidgetContainer {
  GUI* ctx;
  uint8_t column_id;
  uint8_t row_id;

  std::unordered_map<std::string, Label*> labels;
  std::unordered_map<std::string, Image*> images;
  std::unordered_map<std::string, Dropdown*> dropdowns;
  std::unordered_map<std::string, Chart*> charts;
  std::unordered_map<std::string, Container*> containers;
  std::unordered_map<std::string, Spinner*> spinners;
  std::unordered_map<std::string, Button*> buttons;

  uint32_t counter;

  Tile(GUI& ctx, lv_obj_t* tile_id, uint8_t c_id, uint8_t r_id);

 public:
  Label& createLabel(WidgetContainer& parent, std::string name);
  Chart& createChart(WidgetContainer& parent, std::string name);
  Image& createImage(WidgetContainer& parent, std::string name);
  Dropdown& createDropdown(WidgetContainer& parent, std::string name);
  Container& createContainer(WidgetContainer& parent, std::string name);
  Spinner& createSpinner(WidgetContainer& parent, std::string name);
  Button& createButton(WidgetContainer& parent, std::string name);

  Tile& getTile() override;
  WidgetContainer& getParent() override;
  Label& addLabel(std::string name = nextIdString()) override;
  Chart& addChart(std::string name = nextIdString()) override;
  Image& addImage(std::string name = nextIdString()) override;
  Container& addContainer(std::string name = nextIdString()) override;
  Dropdown& addDropdown(std::string name = nextIdString()) override;
  Spinner& addSpinner(std::string name = nextIdString()) override;
  Button& addButton(std::string name = nextIdString()) override;

  Dropdown& getDropdown(const std::string& name) override;
  Label& getLabel(std::string name) { return *labels.at(name); }
  Tile& focusOn();

  void clear();

  ~Tile();
  friend class GUI;
  friend class Popup;
};

#endif

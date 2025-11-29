#ifndef GUI_POPUP_H
#define GUI_POPUP_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <lvgl.h>
#include "Label.h"
#include "Widget.h"

class Popup : public WidgetContainer {
  Tile content;

  uint32_t counter;
  Popup(GUI& ctx, lv_obj_t* tile_id);

 public:
  void clear();
  ~Popup();

  //Add a new label widget as the child of this widget container
  Container& addContainer(std::string name = nextIdString()) override;

  //Add a new label widget as the child of this widget container
  Label& addLabel(std::string name = nextIdString()) override;

  //Add a new label widget as the child of this widget container
  Image& addImage(std::string name = nextIdString()) override;

  //Add a new label widget as the child of this widget container
  Dropdown& addDropdown(std::string name = nextIdString()) override;

  Dropdown& getDropdown(const std::string& name) override;
  //Add a new label widget as the child of this widget container
  Chart& addChart(std::string name = nextIdString()) override;

  //Get a reference to the parent tile container
  Tile& getTile() override;

  //Get a reference to the parent widget/container
  WidgetContainer& getParent() override;

  Popup& addTitle(const std::string& title);
  Popup& addButton(const std::string& title, lv_event_cb_t event_cb,
                   void* user_data = nullptr);

  friend class GUI;
};

#endif

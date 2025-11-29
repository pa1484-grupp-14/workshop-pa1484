#ifndef GUI_H
#define GUI_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "fonts/fonts.h"

class GUI;
#include <lvgl.h>
#include "WidgetContainer.h"

#include "Tile.h"

#include "Widget.h"

#include "Chart.h"
#include "Container.h"
#include "Dropdown.h"
#include "Image.h"
#include "Label.h"
#include "Spinner.h"

#include "Popup.h"

class GUI {
  std::optional<Popup> current_popup;
  lv_obj_t* tileview;
  std::vector<Tile> tiles;

 public:
  //Opens the current popup in the ui, if one doesn't exist, it will be created
  Popup& openPopup();
  //Close the current popup and start with another one, if one doesn't exist, it will be created
  Popup& switchPopup();
  //Close the currently opened popup, if one doesn't exist, this does nothing.
  void closePopup();

  Tile& operator[](int index) { return this->getTile(index); }
  Tile& getTile(int id) { return tiles.at(id); }
  Tile& addTile();
  int nrOfTiles();
  lv_obj_t* getTileView();
  GUI& init() {
    tileview = lv_tileview_create(lv_scr_act());
    lv_obj_set_size(tileview, lv_disp_get_hor_res(NULL),
                    lv_disp_get_ver_res(NULL));
    lv_obj_set_scrollbar_mode(tileview, LV_SCROLLBAR_MODE_OFF);
    return *this;
  }
  void scrollToTile(int id);
  ~GUI();
  GUI();
};

class Component {
 public:
  virtual void constructUI(Tile* gui) = 0;
  virtual void process() = 0;
};

#endif

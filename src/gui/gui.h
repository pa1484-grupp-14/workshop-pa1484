#ifndef GUI_H
#define GUI_H

#include <unordered_map>
#include <utility>
#include <memory>
#include <string>
#include <vector>

class GUI;
#include "lvgl/lvgl.h"
#include "widgets.h"
#include "container.h"
#include "chart.h"
#include "label.h"
#include "dropdown.h"
#include "image.h"
#include "tile.h"

class GUI {
    lv_obj_t* tileview;
    std::vector<Tile> tiles;

    public:

    Tile& operator[](int index) {
        return this->getTile(index);
    }
    Tile& getTile(int id) {
        return tiles.at(id);
    }
    Tile& addTile();
    int nrOfTiles();
    lv_obj_t* getTileView();
    GUI& init() {
        tileview = lv_tileview_create(lv_scr_act());
        lv_obj_set_size(tileview, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
        lv_obj_set_scrollbar_mode(tileview, LV_SCROLLBAR_MODE_OFF);
        return *this;
    }
    ~GUI();
    GUI();
};

#endif

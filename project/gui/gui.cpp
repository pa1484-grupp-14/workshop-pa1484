
#include "gui.h"
#include "lvgl/lvgl.h"


GUI::~GUI() {}

GUI::GUI() {
    tileview = nullptr;
}

lv_obj_t* GUI::getTileView() {
    return tileview;
}

int GUI::nrOfTiles() {
    return tiles.size();
}

Tile& GUI::addTile() {
    uint8_t c_id = this->nrOfTiles();
    uint8_t r_id = 0;
    lv_dir_t dir = lv_dir_t::LV_DIR_HOR;
    lv_obj_t* tile_ptr = lv_tileview_add_tile(this->getTileView(), c_id, r_id, dir);
    tiles.push_back(std::move(Tile(*this, tile_ptr, c_id, r_id)));
    return tiles.back();
}

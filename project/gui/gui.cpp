
#include "gui.h"


GUI::~GUI() {}

GUI::GUI(): current_popup(*this, nullptr) {
    tileview = nullptr;
}

Popup& GUI::OpenPopup() {
    this->current_popup = Popup(*this, lv_msgbox_create(nullptr));
}
void GUI::ClosePopup() {
    this->current_popup = Popup(*this, nullptr);
}


lv_obj_t* GUI::getTileView() {
    return tileview;
}

int GUI::nrOfTiles() {
    return tiles.size();
}

void GUI::scrollToTile(int id) {
    lv_tileview_set_tile_by_index(this->getTileView(), id, 0, LV_ANIM_OFF);
}
Tile& GUI::addTile() {
    uint8_t c_id = this->nrOfTiles();
    uint8_t r_id = 0;
    lv_dir_t dir = lv_dir_t::LV_DIR_HOR;
    lv_obj_t* tile_ptr = lv_tileview_add_tile(this->getTileView(), c_id, r_id, dir);
    tiles.push_back(std::move(Tile(*this, tile_ptr, c_id, r_id)));
    return tiles.back();
}

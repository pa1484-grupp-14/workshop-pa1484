
#include "gui.h"


GUI::~GUI() {}

GUI::GUI(): current_popup() {
    tileview = nullptr;
}

Popup& GUI::OpenPopup() {
    if(current_popup.has_value()) {
        this->ClosePopup();
    } 
    this->current_popup = std::optional<Popup>{Popup(*this, lv_msgbox_create(nullptr))};
    current_popup.value().setSize(550, 400);
    return current_popup.value();
}
void GUI::ClosePopup() {
    if(current_popup.has_value()) {
        current_popup.value().clear();
        lv_msgbox_close(current_popup.value().getWidgetPtr());
    }
    this->current_popup = {};
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

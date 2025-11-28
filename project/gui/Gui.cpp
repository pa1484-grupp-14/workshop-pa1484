
#include "Gui.h"

GUI::~GUI() {}

GUI::GUI() : current_popup() {
  tileview = nullptr;
}

Popup& GUI::openPopup() {
  if (!current_popup.has_value()) {
    this->current_popup =
        std::optional<Popup>{Popup(*this, lv_msgbox_create(nullptr))};
    current_popup.value().setSize(550, 400);
  }

  return current_popup.value();
}

Popup& GUI::switchPopup() {
  if (current_popup.has_value()) {
    this->closePopup();
  }

  return this->openPopup();
}

void GUI::closePopup() {
  if (current_popup.has_value()) {
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
  lv_obj_t* tile_ptr =
      lv_tileview_add_tile(this->getTileView(), c_id, r_id, dir);
  tiles.push_back(std::move(Tile(*this, tile_ptr, c_id, r_id)));
  return tiles.back();
}

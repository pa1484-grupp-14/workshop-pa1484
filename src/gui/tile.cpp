#include "gui.h"

Tile::~Tile() {}

Label& Tile::createLabel(WidgetContainer& parent, std::string name) {
    Label label = Label(parent, counter++);
    labels.emplace(name, std::move(label));
    return labels.at(name);
}
Label& Tile::addLabel(std::string name){
    return this->createLabel(*this, name);
}
Tile::Tile(GUI& ctx, lv_obj_t* tile_id, uint8_t c_id, uint8_t r_id): WidgetContainer(tile_id) {
    this->ctx = &ctx;
    column_id = c_id;
    row_id = r_id;
}
Tile& Tile::getTile() {
    return *this;
}
WidgetContainer& Tile::getParent() {
    return *this;
}

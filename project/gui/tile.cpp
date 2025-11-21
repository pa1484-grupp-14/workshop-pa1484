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

Chart& Tile::createChart(WidgetContainer& parent, std::string name) {
    Chart label = Chart(parent, counter++);
    charts.emplace(name, std::move(label));
    return charts.at(name);
}
Chart& Tile::addChart(std::string name) {
    return this->createChart(*this, name);
}

Container& Tile::createContainer(WidgetContainer& parent, std::string name) {
    Container label = Container(parent, counter++);
    containers.emplace(name, std::move(label));
    return containers.at(name);
}
Container& Tile::addContainer(std::string name) {
    return this->createContainer(*this, name);
}

Image& Tile::createImage(WidgetContainer& parent, std::string name) {
    Image label = Image(parent, counter++);
    images.emplace(name, std::move(label));
    return images.at(name);
}
Image& Tile::addImage(std::string name) {
    return this->createImage(*this, name);
}
Dropdown& Tile::createDropdown(WidgetContainer& parent, std::string name) {
    Dropdown label = Dropdown(parent, counter++);
    dropdowns.emplace(name, std::move(label));
    return dropdowns.at(name);
}
Dropdown& Tile::addDropdown(std::string name) {
    return this->createDropdown(*this, name);
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

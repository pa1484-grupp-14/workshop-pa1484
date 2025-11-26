#include "gui.h"

Popup::~Popup() {}

Label& Popup::createLabel(WidgetContainer& parent, std::string name) {
    Label label = Label(parent, counter++);
    labels.emplace(name, std::move(label));
    return labels.at(name);
}
Label& Popup::addLabel(std::string name){
    return this->createLabel(*this, name);
}

Chart& Popup::createChart(WidgetContainer& parent, std::string name) {
    Chart label = Chart(parent, counter++);
    charts.emplace(name, std::move(label));
    return charts.at(name);
}
Chart& Popup::addChart(std::string name) {
    return this->createChart(*this, name);
}

Container& Popup::createContainer(WidgetContainer& parent, std::string name) {
    Container label = Container(parent, counter++);
    containers.emplace(name, std::move(label));
    return containers.at(name);
}
Container& Popup::addContainer(std::string name) {
    return this->createContainer(*this, name);
}

Image& Popup::createImage(WidgetContainer& parent, std::string name) {
    Image label = Image(parent, counter++);
    images.emplace(name, std::move(label));
    return images.at(name);
}
Image& Popup::addImage(std::string name) {
    return this->createImage(*this, name);
}
Dropdown& Popup::createDropdown(WidgetContainer& parent, std::string name) {
    Dropdown label = Dropdown(parent, counter++);
    dropdowns.emplace(name, std::move(label));
    return dropdowns.at(name);
}
Dropdown& Popup::addDropdown(std::string name) {
    return this->createDropdown(*this, name);
}



Popup::Popup(GUI& ctx, lv_obj_t* tile_id): WidgetContainer(tile_id) {
    this->ctx = &ctx;
}
Tile& Popup::getTile() {
    static int todo = 0;
    return (Tile&)todo;
}

WidgetContainer& Popup::getParent() {
    return *this;
}

#include "Tile.h"

#include "Chart.h"
#include "Container.h"
#include "Dropdown.h"
#include "Image.h"
#include "Label.h"
#include "Spinner.h"
#include "Button.h"
#include "Scale.h"
Tile::~Tile() {}

Label& Tile::createLabel(WidgetContainer& parent, std::string name) {
  Label* label = new Label(parent, counter++);
  labels.emplace(name, label);
  return *labels.at(name);
}
Label& Tile::addLabel(std::string name) {
  return this->createLabel(*this, name);
}

Chart& Tile::createChart(WidgetContainer& parent, std::string name) {
  Chart* label = new Chart(parent, counter++);
  charts.emplace(name, label);
  return *charts.at(name);
}
Chart& Tile::addChart(std::string name) {
  return this->createChart(*this, name);
}

void Tile::clear() {
  labels.clear();
  images.clear();
  dropdowns.clear();
  charts.clear();
  containers.clear();
  spinners.clear();
  buttons.clear();
  scales.clear();
  lv_obj_clean(this->getWidgetPtr());
}

Spinner& Tile::createSpinner(WidgetContainer& parent, std::string name) {
  Spinner* label = new Spinner(parent, counter++);
  
  spinners.emplace(name, std::move(label));
  return *spinners.at(name);
}

Spinner& Tile::addSpinner(std::string name) {
  return this->createSpinner(*this, name);
}

Button& Tile::createButton(WidgetContainer& parent, std::string name) {
  Button* label = new Button(parent, counter++);
  
  buttons.emplace(name, std::move(label));
  return *buttons.at(name);
}

Button& Tile::addButton(std::string name) {
  return this->createButton(*this, name);
}

Container& Tile::createContainer(WidgetContainer& parent, std::string name) {
  Container* label = new Container(parent, counter++);
  containers.emplace(name, label);
  return *containers.at(name);
}
Container& Tile::addContainer(std::string name) {
  return this->createContainer(*this, name);
}

Image& Tile::createImage(WidgetContainer& parent, std::string name) {
  Image* label = new Image(parent, counter++);
  images.emplace(name, label);
  return *images.at(name);
}
Image& Tile::addImage(std::string name) {
  return this->createImage(*this, name);
}
Scale& Tile::createScale(WidgetContainer& parent, std::string name) {
  Scale* label = new Scale(parent, counter++);
  scales.emplace(name, label);
  return *scales.at(name);
}
Scale& Tile::addScale(std::string name) {
  return this->createScale(*this, name);
}
Dropdown& Tile::createDropdown(WidgetContainer& parent, std::string name) {
  Dropdown* label = new Dropdown(parent, counter++);
  dropdowns.emplace(name, label);
  return *dropdowns.at(name);
}
Dropdown& Tile::addDropdown(std::string name) {
  return this->createDropdown(*this, name);
}

Dropdown& Tile::getDropdown(const std::string& name) {
  return *dropdowns.at(name);
}

Tile::Tile(GUI& ctx, lv_obj_t* tile_id, uint8_t c_id, uint8_t r_id)
    : WidgetContainer(tile_id) {
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

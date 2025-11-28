#include "WidgetContainer.h"

#include "Widget.h"

#include "Tile.h"

#include "Chart.h"
#include "Container.h"
#include "Dropdown.h"
#include "Image.h"
#include "Label.h"

Widget& Widget::focusOn() {
  lv_group_focus_obj(this->getWidgetPtr());
  return *this;
}
Widget::Widget(WidgetContainer* parent, lv_obj_t* widget, uint32_t id)
    : WidgetContainer(widget) {
  this->tile = &parent->getTile();
  this->parent = parent;
  this->id = id;
}

Widget& Widget::addEventCallback(lv_event_cb_t event_cb, lv_event_code_t filter,
                                 void* user_data) {
  lv_obj_add_event_cb(this->getWidgetPtr(), event_cb, filter, user_data);
  return *this;
}
Tile& Widget::getTile() {
  return *tile;
}

Container& Widget::addContainer(std::string name) {
  return this->getTile().createContainer(*this, name);
}

Label& Widget::addLabel(std::string name) {
  return this->getTile().createLabel(*this, name);
}

Image& Widget::addImage(std::string name) {
  return this->getTile().createImage(*this, name);
}

Dropdown& Widget::addDropdown(std::string name) {
  return this->getTile().createDropdown(*this, name);
}

Dropdown& Widget::getDropdown(const std::string& name) {
  return this->getTile().getDropdown(name);
}

Chart& Widget::addChart(std::string name) {
  return this->getTile().createChart(*this, name);
}

Widget& Widget::addFlag(lv_obj_flag_t flag) {
  lv_obj_add_flag(this->getWidgetPtr(), flag);
  return *this;
}

Widget& Widget::removeFlag(lv_obj_flag_t flag) {
  lv_obj_remove_flag(this->getWidgetPtr(), flag);
  return *this;
}

Widget& Widget::setPos(int32_t x, int32_t y) {
  lv_obj_set_pos(this->getWidgetPtr(), x, y);
  return *this;
}

Widget& Widget::setX(int32_t x) {
  lv_obj_set_x(this->getWidgetPtr(), x);
  return *this;
}

Widget& Widget::setY(int32_t y) {
  lv_obj_set_y(this->getWidgetPtr(), y);
  return *this;
}

Widget& Widget::setAlign(lv_align_t align) {
  lv_obj_set_align(this->getWidgetPtr(), align);
  return *this;
}

Widget& Widget::setTextAlign(lv_text_align_t align,
                             lv_style_selector_t selector) {
  lv_obj_set_style_text_align(this->getWidgetPtr(), align, selector);
  return *this;
}

Widget& Widget::align(lv_align_t align, int32_t x_offset, int32_t y_offset) {
  lv_obj_align(this->getWidgetPtr(), align, x_offset, y_offset);
  return *this;
}

Widget& Widget::alignTo(Widget& base, lv_align_t align, int32_t x_offset,
                        int32_t y_offset) {
  lv_obj_align_to(this->getWidgetPtr(), base.getWidgetPtr(), align, x_offset,
                  y_offset);
  return *this;
}

Widget& Widget::center() {
  lv_obj_center(this->getWidgetPtr());
  return *this;
}

Widget& Widget::setFont(const lv_font_t* font, lv_style_selector_t selector) {
  lv_obj_set_style_text_font(this->getWidgetPtr(), font, selector);
  return *this;
}
Widget& Widget::setGridCell(int32_t row_pos, int32_t col_pos, int32_t row_span,
                            int32_t col_span, lv_grid_align_t row_align,
                            lv_grid_align_t column_align) {
  lv_obj_set_grid_cell(this->getWidgetPtr(), column_align, col_pos, col_span,
                       row_align, row_pos, row_span);
  return *this;
}

WidgetContainer& Widget::getParent() {
  return *parent;
}

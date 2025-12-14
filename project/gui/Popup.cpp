#include "Popup.h"

Popup::~Popup() {}
void Popup::clear() {
  content = Tile(*content.ctx, content.getWidgetPtr(), 0, 0);
}
Popup::Popup(GUI& ctx, lv_obj_t* tile_id)
    : WidgetContainer(tile_id),
      content(ctx, lv_msgbox_get_content(this->getWidgetPtr()), 0, 0) {}
Dropdown& Popup::getDropdown(const std::string& name) {
  return content.getDropdown(name);
}

//Add a new label widget as the child of this widget container
Container& Popup::addContainer(std::string name) {
  return content.addContainer(name);
}

//Add a new label widget as the child of this widget container
Label& Popup::addLabel(std::string name) {
  return content.addLabel(name);
}

//Add a new label widget as the child of this widget container
Scale& Popup::addScale(std::string name) {
  return content.addScale(name);
}

//Add a new label widget as the child of this widget container
Image& Popup::addImage(std::string name) {
  return content.addImage(name);
}
//Add a new label widget as the child of this widget container
Button& Popup::addButton(std::string name) {
  return content.addButton(name);
}

Spinner& Popup::addSpinner(std::string name) {
  return content.addSpinner();
}
//Add a new label widget as the child of this widget container
Dropdown& Popup::addDropdown(std::string name) {
  return content.addDropdown(name);
}

//Add a new label widget as the child of this widget container
Chart& Popup::addChart(std::string name) {
  return content.addChart(name);
}

//Get a reference to the parent tile container
Tile& Popup::getTile() {
  return content;
}

//Get a reference to the parent widget/container
WidgetContainer& Popup::getParent() {
  return content;
}

Popup& Popup::addTitle(const std::string& title) {
  auto a = lv_msgbox_add_title(this->getWidgetPtr(), title.c_str());
  lv_obj_set_style_text_font(a, &lv_font_montserrat_48, LV_PART_MAIN);

  return *this;
}
Popup& Popup::addButton(const std::string& title, lv_event_cb_t event_cb,
                        void* user_data) {
  auto a = lv_msgbox_add_footer_button(this->getWidgetPtr(), title.c_str());
  lv_obj_set_style_text_font(a, &lv_font_montserrat_48, LV_PART_MAIN);
  lv_obj_set_height(lv_msgbox_get_footer(this->getWidgetPtr()), 70);
  lv_obj_add_event_cb(a, event_cb, LV_EVENT_CLICKED, user_data);

  return *this;
}

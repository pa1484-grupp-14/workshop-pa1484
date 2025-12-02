#include "Dropdown.h"

Dropdown::Dropdown(WidgetContainer& parent, uint32_t id)
    : Widget((WidgetContainer*)&parent.getTile(),
             lv_dropdown_create(parent.getWidgetPtr()), id) {}

Dropdown& Dropdown::setText(std::string text) {
  lv_dropdown_set_text(this->getWidgetPtr(), text.c_str());
  return *this;
}

Dropdown& Dropdown::setOptions(const std::string& text) {
  lv_dropdown_set_options(this->getWidgetPtr(), text.c_str());
  return *this;
}

Dropdown& Dropdown::toggleOption(int id) {
  lv_dropdown_set_selected(this->getWidgetPtr(), static_cast<uint16_t>(id));
  return *this;
}

Dropdown& Dropdown::setOptions(const std::vector<std::string>& text) {

  lv_dropdown_clear_options(this->getWidgetPtr());

  for (size_t i = 0; i < text.size(); i++) {

    lv_dropdown_add_option(this->getWidgetPtr(), text[i].c_str(), i);
  }

  return *this;
}

Dropdown& Dropdown::pushOption(const std::string& new_option) {

  auto len = lv_dropdown_get_option_count(this->getWidgetPtr());

  lv_dropdown_add_option(this->getWidgetPtr(), new_option.c_str(), len);

  return *this;
}

Dropdown& Dropdown::addOption(std::string& text, uint32_t pos) {
  lv_dropdown_add_option(this->getWidgetPtr(), text.c_str(), pos);
  return *this;
}

uint32_t Dropdown::getSelectedItem() {
  return lv_dropdown_get_selected(this->getWidgetPtr());
}

Dropdown& Dropdown::setListFont(const lv_font_t* font,
                                lv_style_selector_t selector) {
  auto list_widget = lv_dropdown_get_list(this->getWidgetPtr());
  lv_obj_set_style_text_font(list_widget, font, selector);
  return *this;
}

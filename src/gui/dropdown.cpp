#include "gui.h"


Dropdown::Dropdown(WidgetContainer& parent, uint32_t id): Widget(parent.getTile(), lv_dropdown_create(parent.getWidgetPtr()), id) {}

Dropdown& Dropdown::setText(std::string text) {
    lv_dropdown_set_text(this->getWidgetPtr(), text.c_str());
    return *this;
}

Dropdown& Dropdown::setOptions(const std::string& text) {
    lv_dropdown_set_options(this->getWidgetPtr(), text.c_str());
    return *this;
}

Dropdown& Dropdown::addOption(std::string& text, uint32_t pos) {
    lv_dropdown_add_option(this->getWidgetPtr(), text.c_str(), pos);
    return *this;
}

uint32_t Dropdown::getSelectedItem() {
    return lv_dropdown_get_selected(this->getWidgetPtr());
}


Dropdown& Dropdown::setListFont(const lv_font_t* font, lv_style_selector_t selector) {
    auto list_widget = lv_dropdown_get_list(this->getWidgetPtr());
    lv_obj_set_style_text_font(list_widget, font, selector);
    return *this;
}

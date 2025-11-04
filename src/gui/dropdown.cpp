#include "gui.h"


Dropdown::Dropdown(WidgetContainer& parent, u_int32_t id): Widget(parent.getTile(), lv_dropdown_create(parent.getWidgetPtr()), id) {}

Dropdown& Dropdown::setText(std::string text) {
    lv_dropdown_set_text(this->getWidgetPtr(), text.c_str());
    return *this;
}

Dropdown& Dropdown::setOptions(std::string& text) {
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
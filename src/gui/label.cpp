#include "gui.h"

Label::Label(WidgetContainer& parent, u_int32_t id): Widget(parent.getTile(), lv_label_create(parent.getWidgetPtr()), id) {}
Label& Label::setText(std::string text) {
    lv_label_set_text(this->getWidgetPtr(), text.c_str());
    return *this;
}
Label& Label::setFont(const lv_font_t* font, lv_style_selector_t selector) {
    lv_obj_set_style_text_font(this->getWidgetPtr(), font, selector);
    return *this;
}
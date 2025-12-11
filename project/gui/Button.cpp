#include "Button.h"

Button::Button(WidgetContainer& parent, uint32_t id): Widget(&parent, lv_button_create(parent.getWidgetPtr()), id) {}

Button& Button::setBtnText(const std::string& text) {
    lv_obj_t* label_ptr = lv_label_create(this->getWidgetPtr());
    lv_label_set_text(label_ptr, text.c_str());
    return *this;
}


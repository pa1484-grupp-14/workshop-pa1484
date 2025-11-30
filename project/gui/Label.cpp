#include "Label.h"

Label::Label(WidgetContainer& parent, uint32_t id): Widget((WidgetContainer*)&parent.getTile(), lv_label_create(parent.getWidgetPtr()), id) {}
Label& Label::setText(std::string text) {
    lv_label_set_text(this->getWidgetPtr(), text.c_str());
    return *this;
}

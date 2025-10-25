#pragma once
#include "gui.h"

class Label: public Widget {
    public:
    Label(WidgetContainer& parent, uint32_t id);
    Label& setText(std::string text);
    Label& setFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN);
};

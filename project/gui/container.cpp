#include "gui.h"

Container::Container(WidgetContainer& parent, uint32_t id): Widget(parent, lv_obj_create(parent.getWidgetPtr()), id) {}

static bool uninited = true;
Container& Container::disableFrame() {
    static lv_style_t style_shadow;
    
    if (uninited) {
            lv_style_init(&style_shadow);
    lv_style_set_border_opa(&style_shadow, 0);
    lv_style_set_bg_opa(&style_shadow, 0);
    uninited = false;
    }


    lv_obj_add_style(this->getWidgetPtr(), &style_shadow, 0);
    return *this;
}
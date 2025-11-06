#include "gui.h"
Image::Image(WidgetContainer& parent, u_int32_t id): Widget(parent.getTile(), lv_image_create(parent.getWidgetPtr()), id) {}
Image& Image::setSource(lv_image_dsc_t* src) {
    lv_image_set_src(this->getWidgetPtr(), src);
    return *this;
}
Image& Image::setScale() {
    lv_image_set_scale();
    return *this;
}
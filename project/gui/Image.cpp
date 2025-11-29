#include "Image.h"
Image::Image(WidgetContainer& parent, uint32_t id)
    : Widget((WidgetContainer*)&parent.getTile(),
             lv_image_create(parent.getWidgetPtr()), id) {}

Image& Image::setSource(const lv_image_dsc_t* src) {
  lv_image_set_src(this->getWidgetPtr(), src);
  return *this;
}

Image& Image::setScale(float scale) {
  lv_image_set_scale(this->getWidgetPtr(), (uint32_t)(scale * 256.f));
  return *this;
}

#include "gui.h"
Image::Image(WidgetContainer& parent, u_int32_t id): Widget(parent.getTile(), lv_image_create(parent.getWidgetPtr()), id) {}

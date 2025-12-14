#include "Scale.h"

Scale::Scale(WidgetContainer& parent, uint32_t id): Widget((WidgetContainer*)&parent.getTile(), lv_scale_create(parent.getWidgetPtr()), id) {}

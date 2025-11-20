#include "gui.h"

Container::Container(WidgetContainer& parent, uint32_t id): Widget(parent.getTile(), lv_obj_create(parent.getWidgetPtr()), id) {}

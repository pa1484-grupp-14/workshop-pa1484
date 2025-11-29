#include "Button.h"

Button::Button(WidgetContainer& parent, uint32_t id): Widget(&parent, lv_button_create(parent.getWidgetPtr()), id) {}
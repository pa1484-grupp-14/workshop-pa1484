#include "gui.h"

Spinner::Spinner(WidgetContainer& parent, uint32_t id): Widget(parent, lv_spinner_create(parent.getWidgetPtr()), id) {}

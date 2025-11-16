#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include "gui.h"

class Container : public Widget {

public:
    Container(WidgetContainer& parent, uint32_t id);
};
#endif

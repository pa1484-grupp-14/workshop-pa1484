#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include "Widget.h"

class Container : public Widget {

public:
    Container(WidgetContainer& parent, uint32_t id);
    Container& disableFrame();
};
#endif

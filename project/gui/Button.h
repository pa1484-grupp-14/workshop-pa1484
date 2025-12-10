#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "Widget.h"

class Button: public Widget {
    
public:
    Button(WidgetContainer& parent, uint32_t id);
    Button& setBtnText(const std::string& text);
};

#endif

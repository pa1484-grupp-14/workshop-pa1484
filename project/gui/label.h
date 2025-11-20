#ifndef GUI_LABEL_H
#define GUI_LABEL_H
#include "gui.h"

class Label: public Widget {
    public:
    Label(WidgetContainer& parent, uint32_t id);
    ///# Label::setText
    ///
    /// Sets the text attribute of the label to the provided string
    Label& setText(std::string text);
};
#endif
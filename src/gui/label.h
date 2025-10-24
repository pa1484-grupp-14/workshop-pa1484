#pragma once

class Label: public Widget {
    public:
    Label(WidgetContainer& parent, uint32_t id);
    Label& setText(std::string text);
};

#ifndef GUI_POPUP_H
#define GUI_POPUP_H

#include <unordered_map>
#include <utility>
#include <memory>
#include <string>
#include <vector>

#include <lvgl.h>
#include "widgets.h"
#include "label.h"



class Popup: public WidgetContainer {
    GUI* ctx;

    std::unordered_map<std::string, Label> labels;
    std::unordered_map<std::string, Image> images;
    std::unordered_map<std::string, Dropdown> dropdowns;
    std::unordered_map<std::string, Chart> charts;
    std::unordered_map<std::string, Container> containers;

    uint32_t counter;
    Popup(GUI& ctx, lv_obj_t* tile_id);
    public:

    Label& createLabel(WidgetContainer& parent, std::string name);
    Chart& createChart(WidgetContainer& parent, std::string name);
    Image& createImage(WidgetContainer& parent, std::string name);
    Dropdown& createDropdown(WidgetContainer& parent, std::string name);
    Container& createContainer(WidgetContainer& parent, std::string name);
    Tile& getTile() override;
    WidgetContainer& getParent() override;
    Label& addLabel(std::string name = nextIdString()) override;
    Chart& addChart(std::string name = nextIdString()) override;
    Image& addImage(std::string name = nextIdString()) override;
    Container& addContainer(std::string name = nextIdString()) override;
    Dropdown& addDropdown(std::string name = nextIdString()) override;
    Label& getLabel(std::string name) {
        return labels.at(name);
    }
    ~Popup();
    friend class GUI;
};

#endif

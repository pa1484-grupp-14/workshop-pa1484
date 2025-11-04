#ifndef GUI_TILE_H
#define GUI_TILE_H

#include <unordered_map>
#include <utility>
#include <memory>
#include <string>
#include <vector>

#include "lvgl/lvgl.h"
#include "widgets.h"
#include "label.h"

class Tile: public WidgetContainer {
    GUI* ctx;
    uint8_t column_id;
    uint8_t row_id;

    std::unordered_map<std::string, Label> labels;
    uint32_t counter;

    Tile(GUI& ctx, lv_obj_t* tile_id, uint8_t c_id, uint8_t r_id);
    public:

    Label& createLabel(WidgetContainer& parent, std::string name);
    Tile& getTile() override;
    WidgetContainer& getParent() override;
    Label& addLabel(std::string name = nextIdString()) override;
    Label& getLabel(std::string name) {
        return labels.at(name);
    }
    ~Tile();
    friend class GUI;
};
#endif
#ifndef GUI_CHART_H

#define GUI_CHART_H
#include "gui.h"
#include <unordered_map>
class Chart: public Widget {
    std::unordered_map<std::string, lv_chart_series_t*> series;
    public:
    ~Chart();
    Chart(WidgetContainer& parent, uint32_t id);   
    Chart& setType(lv_chart_type_t type);
    Chart& addSeries(std::string& name, lv_color_t color, lv_chart_axis_t axis);
    Chart& addPoint(std::string& series_name, int32_t value);
    Chart& refresh();
    Chart& setCursorPos(lv_chart_cursor_t *cursor, lv_point_t *pos);
};

#endif
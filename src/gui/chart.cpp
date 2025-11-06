
#include "gui.h"

Chart::Chart(WidgetContainer& parent, u_int32_t id): Widget(parent.getTile(), lv_chart_create(parent.getWidgetPtr()), id) {}

Chart& Chart::setType(lv_chart_type_t type) {
    lv_chart_set_type(this->getWidgetPtr(), type);
    return *this;
}

Chart& Chart::addSeries(std::string& name, lv_color_t color, lv_chart_axis_t axis) {
    series.emplace(name, lv_chart_add_series(this->getWidgetPtr(), color, axis));
    return *this;
}

Chart& Chart::setDivisionLines(uint32_t horizontal_lines, uint32_t vertical_lines) {
    lv_chart_set_div_line_count(this->getWidgetPtr(), horizontal_lines, vertical_lines);
    return *this;
}
Chart& Chart::refresh() {
    lv_chart_refresh(this->getWidgetPtr());
    return *this;
}

Chart& Chart::setCursorPos(lv_chart_cursor_t *cursor, lv_point_t *pos) {
    lv_chart_set_cursor_pos(this->getWidgetPtr(), cursor, pos);
    return *this;
}

Chart& Chart::removeSeries(std::string& name) {
    auto serie = series.at(name);
    lv_chart_remove_series(this->getWidgetPtr(), serie);
    series.erase(name);
    return *this;
}

Chart::~Chart() {
    for(auto serie: series) {
        lv_chart_remove_series(this->getWidgetPtr(), serie.second);
    }
}

Chart& Chart::addPoint(std::string& series_name, int32_t value) {
    auto serie = series.at(series_name);
    lv_chart_set_next_value(this->getWidgetPtr(), serie, value);
    return *this;
}
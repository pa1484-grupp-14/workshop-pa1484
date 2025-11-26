#include "Chart.h"
#include <stdexcept>
#include "Widget.h"

Chart::Chart(WidgetContainer& parent, uint32_t id)
    : Widget((WidgetContainer*)&parent.getTile(),
             lv_chart_create(parent.getWidgetPtr()), id) {}

Chart& Chart::setType(lv_chart_type_t type) {
  lv_chart_set_type(this->getWidgetPtr(), type);
  return *this;
}

Chart& Chart::addSeries(const std::string& name, lv_color_t color,
                        lv_chart_axis_t axis) {
  lv_chart_series_t* serie =
      lv_chart_add_series(this->getWidgetPtr(), color, axis);
  if (serie == nullptr)
    throw std::out_of_range("wat");
  series.emplace(name, serie);
  return *this;
}

Chart& Chart::setDivisionLines(uint32_t horizontal_lines,
                               uint32_t vertical_lines) {
  lv_chart_set_div_line_count(this->getWidgetPtr(), horizontal_lines,
                              vertical_lines);
  return *this;
}
Chart& Chart::refresh() {
  lv_chart_refresh(this->getWidgetPtr());
  return *this;
}
Chart& Chart::setAxisRange(lv_chart_axis_t axis, int32_t min, int32_t max) {
  lv_chart_set_axis_range(this->getWidgetPtr(), axis, min, max);
  return *this;
}

Chart& Chart::setCursorPos(lv_chart_cursor_t* cursor, lv_point_t* pos) {
  lv_chart_set_cursor_pos(this->getWidgetPtr(), cursor, pos);
  return *this;
}

Chart& Chart::removeSeries(const std::string& name) {
  auto serie = series.at(name);
  lv_chart_remove_series(this->getWidgetPtr(), serie);
  series.erase(name);
  return *this;
}

Chart::~Chart() {
  if (this->getRefCount() <= 1) {
    for (auto serie : series) {
      lv_chart_remove_series(this->getWidgetPtr(), serie.second);
    }
  }
}

Chart& Chart::addPoint(const std::string& series_name, int32_t value) {
  lv_chart_series_t* serie = series.at(series_name);
  lv_chart_set_next_value(this->getWidgetPtr(), serie, value);
  return *this;
}

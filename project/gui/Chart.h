#ifndef GUI_CHART_H

#define GUI_CHART_H
#include "Widget.h"
#include <unordered_map>
class Chart: public Widget {
    std::unordered_map<std::string, lv_chart_series_t*> series;
    public:
    ~Chart();
    Chart(WidgetContainer& parent, uint32_t id);
    /// # Set the type of this chart
    /// DEFAULT: the default chart type is a line graph
    Chart& setType(lv_chart_type_t type);

    /// # Set the number of division lines in the chart
    Chart& setDivisionLines(uint32_t horizontal_lines, uint32_t vertical_lines);

    /// # Set the range for the axis along the graph
    Chart& setAxisRange(lv_chart_axis_t axis, int32_t min, int32_t max);

    /// # Add a series to the chart with name `name`
    /// NOTE: by default 10 points are automatically allocated
    Chart& addSeries(const std::string& name, lv_color_t color = lv_palette_main(LV_PALETTE_BLUE), lv_chart_axis_t axis = LV_CHART_AXIS_PRIMARY_Y);

    /// # Remove the series with the name `name`
    /// EXCEPTIONS: if the specified series doesn't exist in the chart, an out of bound exception will be thrown.
    Chart& removeSeries(const std::string& name);

    /// # Add a new point to the chart with name `series_name`
    /// NOTE: the series must previously have been added with the ``Chart::addSeries`` method.
    /// NOTE: remember to call ``Chart::refresh`` after using this method!
    /// EXCEPTIONS: if the specified series doesn't exist in the chart, an out of bound exception will be thrown.
    Chart& addPoint(const std::string& series_name, int32_t value);

    /// # Add new points to the chart with name `series_name`
    /// NOTE: the series must previously have been added with the ``Chart::addSeries`` method.
    /// NOTE: this automatically calls ``Chart::refresh``
    /// EXCEPTIONS: if the specified series doesn't exist in the chart, an out of bound exception will be thrown.
    template<unsigned int N>
    Chart& addPoints(const std::string& series_name, int32_t const (&my_array)[N]) {
        for (int32_t point : my_array) {
            this->addPoint(series_name, point);
        }
        return this->refresh();
    }

    /// # Updates the chart to display the current state of all the included series.
    Chart& refresh();

    /// Set the cursor position in the chart
    Chart& setCursorPos(lv_chart_cursor_t *cursor, lv_point_t *pos);
};

#endif

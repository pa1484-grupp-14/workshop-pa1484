#ifndef GUI_CHART_H

#define GUI_CHART_H
#include "gui.h"
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

    /// # Add a series to the chart with name `name`
    /// NOTE: by default 10 points are automatically allocated
    Chart& addSeries(std::string& name, lv_color_t color, lv_chart_axis_t axis);

    /// # Remove the series with the name `name`
    /// EXCEPTIONS: if the specified series doesn't exist in the chart, an out of bound exception will be thrown.
    Chart& removeSeries(std::string& name);

    /// # Add a new point to the chart with name `series_name`
    /// NOTE: the series must previously have been added with the ``Chart::addSeries`` method.
    /// NOTE: remember to call ``Chart::refresh`` after using this method!
    /// EXCEPTIONS: if the specified series doesn't exist in the chart, an out of bound exception will be thrown.
    Chart& addPoint(std::string& series_name, int32_t value);

    /// # Updates the chart to display the current state of all the included series. 
    Chart& refresh();

    /// Set the cursor position in the chart
    Chart& setCursorPos(lv_chart_cursor_t *cursor, lv_point_t *pos);
};

#endif
#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <lvgl.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "WidgetContainer.h"
#include "gui/Tile.h"

/// # Widget
/// this class implements all generic widget functions from LVGL and should be inherited from for specifi widget wrappers
class Widget : public WidgetContainer {
 private:
  WidgetContainer* parent;
  Tile* tile;
  uint32_t id;

 protected:
  //Object constructor
  Widget(WidgetContainer* parent, lv_obj_t* widget, uint32_t id);

 public:
  // # Destructor function
  ~Widget() {}

  // # Get Parent tile of this Widget
  Tile& getTile() override;

  // # Add label as child of this widget
  Label& addLabel(std::string name = nextIdString()) override;
  // # Add label as child of this widget
  Chart& addChart(std::string name = nextIdString()) override;
  // # Add label as child of this widget
  Image& addImage(std::string name = nextIdString()) override;
  // # Add label as child of this widget
  Dropdown& addDropdown(std::string name = nextIdString()) override;

  Spinner& addSpinner(std::string name = nextIdString()) override;

  Dropdown& getDropdown(const std::string& name) override;

  Container& addContainer(std::string name = nextIdString()) override;
  Button& addButton(std::string name = nextIdString()) override;
  // # Get parent of this widget
  WidgetContainer& getParent() override;

  // # Add an event callback to the widget
  Widget& addEventCallback(lv_event_cb_t event_cb, lv_event_code_t filter,
                           void* user_data = nullptr);

  //FLAGS

  // # Add a widget flag to the widget
  Widget& addFlag(lv_obj_flag_t flag);

  // # Remove a widget flag to the widget
  Widget& removeFlag(lv_obj_flag_t flag);

  Widget& focusOn();

  // Positioning

  // # Set position of the widget
  Widget& setPos(int32_t x, int32_t y);

  // # Set the X coordinate of the widget
  Widget& setX(int32_t x);

  // # Set the Y coordinate of the widget
  Widget& setY(int32_t y);

  // # Set the alignment type of the widget
  Widget& setAlign(lv_align_t align);

  // # Set the alignment type of the widget

  Widget& setTextAlign(lv_text_align_t align,
                       lv_style_selector_t selector = LV_PART_MAIN);

  // # Set the alignment and offset relative to widget parent
  Widget& align(lv_align_t align, int32_t x_offset, int32_t y_offset);

  // # Set the alignment and offset relative to arbitrary widget
  Widget& alignTo(Widget& base, lv_align_t align, int32_t x_offset,
                  int32_t y_offset);

  // # Center widget
  Widget& center();

  // # Set position of the widget
  Widget& setGridCell(int32_t row_pos, int32_t col_pos, int32_t row_span = 1,
                      int32_t col_span = 1,
                      lv_grid_align_t row_align = LV_GRID_ALIGN_CENTER,
                      lv_grid_align_t column_align = LV_GRID_ALIGN_CENTER);

  // Other Styling

  ///# Widget::setFont
  /// @brief Set the font styling of the label
  /// @param font the LVGL font for this label to use
  /// @param selector the part of the label the font applies to (by default the main text)
  /// @return A new reference to the calling label
  Widget& setFont(const lv_font_t* font,
                  lv_style_selector_t selector = LV_PART_MAIN);

  friend class Popup;
};
#endif

#ifndef WIDGET_CONTAINER_H
#define WIDGET_CONTAINER_H
#include <lvgl.h>
#include <string>
#include "WidgetCustomizer.h"

/// # Widget Container
/// this class is the baseline to all widgets (as all widgets in LVGL are really in themselves containers)
/// under the hood this wrappers uses the ``user_data`` field in the wrapped widget as a reference counter
/// in order to allow cloning of the widget container object.
class WidgetContainer : public WidgetCustomizer<WidgetContainer> {

 protected:
  //override copy and move constructors to allow for reference counting
  WidgetContainer(WidgetContainer&& other);
  WidgetContainer(const WidgetContainer& other);

  //override copy and move assignments to allow for reference counting
  WidgetContainer& operator=(const WidgetContainer& other);
  WidgetContainer& operator=(WidgetContainer&& other);

  size_t getRefCount();
  void setRefCount(size_t count);

 public:
  // Set up this widget as a flex container
  WidgetContainer& setFlexLayout(
      lv_flex_flow_t flex_flow, lv_flex_align_t main_align,
      lv_flex_align_t cross_align = LV_FLEX_ALIGN_CENTER,
      lv_flex_align_t cross_place = LV_FLEX_ALIGN_CENTER) override;

  // Set up this widget as a grid container
  WidgetContainer& setGridLayout(const int32_t col_dsc[],
                                 const int32_t row_dsc[]) override;

  // Sizing

  // # Set size of the widget
  WidgetContainer& setSize(int32_t w, int32_t h) override;

  // # Set width of the widget
  WidgetContainer& setWidth(int32_t w) override;

  // # Set height of the widget
  WidgetContainer& setHeight(int32_t h) override;

  // # Set content width of the widget
  WidgetContainer& setContentWidth(int32_t w) override;

  // # Set content height of the widget
  WidgetContainer& setContentHeight(int32_t h) override;

  //Destructor (which deletes and cleans the widget if and only if it holds the last reference to it)
  ~WidgetContainer();

  friend class Tile;
};
#endif

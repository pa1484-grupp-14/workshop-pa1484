#ifndef WIDGET_CUSTOMIZER_H
#define WIDGET_CUSTOMIZER_H
#include <lvgl.h>
#include <string>
class Tile;
class Label;
class Image;
class Chart;
class Dropdown;
class Container;
class WidgetContainer;

static size_t id_generator;
static size_t nextId() {
  return id_generator++;
}

static std::string nextIdString() {
  return "__id" + std::to_string(nextId());
}

template <typename T>
class Sized {
 public:
  //Add a new label widget as the child of this widget container
  virtual Container& addContainer(std::string name = nextIdString()) = 0;

  //Add a new label widget as the child of this widget container
  virtual Label& addLabel(std::string name = nextIdString()) = 0;

  //Add a new label widget as the child of this widget container
  virtual Image& addImage(std::string name = nextIdString()) = 0;

  //Add a new label widget as the child of this widget container
  virtual Dropdown& addDropdown(std::string name = nextIdString()) = 0;

  //Add a new label widget as the child of this widget container
  virtual Chart& addChart(std::string name = nextIdString()) = 0;

  //Get a reference to the parent tile container
  virtual Tile& getTile() = 0;

  //Get a reference to the parent widget/container
  virtual WidgetContainer& getParent() = 0;

  // Set up this widget as a flex container
  virtual T& setFlexLayout(
      lv_flex_flow_t flex_flow, lv_flex_align_t main_align,
      lv_flex_align_t cross_align = LV_FLEX_ALIGN_CENTER,
      lv_flex_align_t cross_place = LV_FLEX_ALIGN_CENTER) = 0;

  // Set up this widget as a grid container
  virtual T& setGridLayout(const int32_t col_dsc[],
                           const int32_t row_dsc[]) = 0;

  // Sizing

  // # Set size of the widget
  virtual T& setSize(int32_t w, int32_t h) = 0;

  // # Set width of the widget
  virtual T& setWidth(int32_t w) = 0;

  // # Set height of the widget
  virtual T& setHeight(int32_t h) = 0;

  // # Set content width of the widget
  virtual T& setContentWidth(int32_t w) = 0;

  // # Set content height of the widget
  virtual T& setContentHeight(int32_t h) = 0;
};
#endif

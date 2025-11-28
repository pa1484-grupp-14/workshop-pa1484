
#include "WidgetContainer.h"
#include <lvgl.h>

size_t WidgetContainer::getRefCount() {
  return (size_t)lv_obj_get_user_data(widget_ptr);
}
void WidgetContainer::setRefCount(size_t count) {
  lv_obj_set_user_data(widget_ptr, (void*)count);
}

WidgetContainer::~WidgetContainer() {
  if (widget_ptr != nullptr && lv_obj_is_valid(widget_ptr)) {
    size_t ref_count = getRefCount();
    if (ref_count > 1) {
      //were not the last object referencing this widget
      ref_count--;
      setRefCount(ref_count);
    } else {
      //we ARE the last object referencing this widget
      lv_obj_clean(widget_ptr);
      lv_obj_delete(widget_ptr);
    }
  }
}

WidgetContainer::WidgetContainer(WidgetContainer&& other) {
  widget_ptr = other.widget_ptr;
  if (widget_ptr != nullptr) {
    //increase reference counter by 1
    size_t ref_count = getRefCount();
    ref_count++;
    setRefCount(ref_count);
  }
};
WidgetContainer::WidgetContainer(const WidgetContainer& other) {
  widget_ptr = other.widget_ptr;
  if (widget_ptr != nullptr) {
    //increase reference counter by 1
    size_t ref_count = getRefCount();
    ref_count++;
    setRefCount(ref_count);
  }
};

WidgetContainer& WidgetContainer::operator=(const WidgetContainer& other) {
  //the only time reference counters change is if we point to different widgets,
  //although if this *wasn't* true, the whole assignment operation is a no-op anyway.
  if (widget_ptr != other.widget_ptr) {
    //destroy old reference
    if (widget_ptr != nullptr) {
      size_t ref_count = getRefCount();
      if (ref_count > 1) {
        ref_count--;
        setRefCount(ref_count);
      } else {
        lv_obj_clean(widget_ptr);
        lv_obj_delete(widget_ptr);
      }
    }
    //reassign
    widget_ptr = other.widget_ptr;
    //create new reference
    if (widget_ptr != nullptr) {
      size_t ref_count = getRefCount();
      ref_count++;
      setRefCount(ref_count);
    }
  }
  return *this;
};
WidgetContainer& WidgetContainer::operator=(WidgetContainer&& other) {
  //the only time reference counters change is if we point to different widgets,
  //although if this *wasn't* true, the whole assignment operation is a no-op anyway.
  if (widget_ptr != other.widget_ptr) {
    //destroy old reference
    if (widget_ptr != nullptr) {
      size_t ref_count = getRefCount();
      if (ref_count > 1) {
        ref_count--;
        setRefCount(ref_count);
      } else {
        lv_obj_clean(widget_ptr);
        lv_obj_delete(widget_ptr);
      }
    }
    //reassign
    widget_ptr = other.widget_ptr;
    //create new reference
    if (widget_ptr != nullptr) {
      size_t ref_count = getRefCount();
      ref_count++;
      setRefCount(ref_count);
    }
  }
  return *this;
};

WidgetContainer::WidgetContainer(lv_obj_t* widget) {
  this->widget_ptr = widget;
  //we *should* be the sole owner of this widget at this point.
  //otherwise the constructor is being used incorrectly.
  setRefCount(getRefCount() + 1);
}

WidgetContainer& WidgetContainer::setSize(int32_t w, int32_t h) {
  lv_obj_set_size(this->getWidgetPtr(), w, h);
  return *this;
}

WidgetContainer& WidgetContainer::setWidth(int32_t w) {
  lv_obj_set_width(this->getWidgetPtr(), w);
  return *this;
}

WidgetContainer& WidgetContainer::setHeight(int32_t h) {
  lv_obj_set_height(this->getWidgetPtr(), h);
  return *this;
}

WidgetContainer& WidgetContainer::setContentWidth(int32_t w) {
  lv_obj_set_content_width(this->getWidgetPtr(), w);
  return *this;
}

WidgetContainer& WidgetContainer::setContentHeight(int32_t h) {
  lv_obj_set_content_height(this->getWidgetPtr(), h);
  return *this;
}

WidgetContainer& WidgetContainer::setFlexLayout(lv_flex_flow_t layout,
                                                lv_flex_align_t a,
                                                lv_flex_align_t b,
                                                lv_flex_align_t c) {
  lv_obj_set_layout(this->getWidgetPtr(), LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(this->getWidgetPtr(), layout);
  lv_obj_set_flex_align(this->getWidgetPtr(), a, b, c);
  return *this;
}

WidgetContainer& WidgetContainer::setGridLayout(const int32_t col_dsc[],
                                                const int32_t row_dsc[]) {
  lv_obj_set_layout(this->getWidgetPtr(), LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(this->getWidgetPtr(), col_dsc, row_dsc);
  return *this;
}

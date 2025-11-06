
#include "gui.h"
#include "lvgl/lvgl.h"


WidgetContainer::~WidgetContainer() {
    if(widget_ptr != nullptr) {
        size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
        if (ref_count > 1) {
            //were not the last object referencing this widget
            ref_count--;
            lv_obj_set_user_data(widget_ptr, (void*)ref_count);
        } else {
            //we ARE the last object referencing this widget
            lv_obj_clean(widget_ptr);
            lv_obj_delete(widget_ptr);
        }
    }
}
WidgetContainer::WidgetContainer(WidgetContainer&& other) {
    widget_ptr = other.widget_ptr;
    if(widget_ptr != nullptr) {
        //increase reference counter by 1
        size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
        ref_count++;
        lv_obj_set_user_data(widget_ptr, (void*)ref_count);
    }
};
WidgetContainer::WidgetContainer(const WidgetContainer& other) {
    widget_ptr = other.widget_ptr;
    if(widget_ptr != nullptr) {
        //increase reference counter by 1
        size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
        ref_count++;
        lv_obj_set_user_data(widget_ptr, (void*)ref_count);
    }

};

WidgetContainer& WidgetContainer::operator=(const WidgetContainer& other) {
    //the only time reference counters change is if we point to different widgets,
    //although if this *wasn't* true, the whole assignment operation is a no-op anyway.
    if(widget_ptr != other.widget_ptr) {
        //destroy old reference
        if(widget_ptr != nullptr) {
            size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
            if (ref_count > 1) {
                ref_count--;
                lv_obj_set_user_data(widget_ptr, (void*)ref_count);
            } else {
                lv_obj_clean(widget_ptr);
                lv_obj_delete(widget_ptr);
            }
        }
        //reassign
        widget_ptr = other.widget_ptr;
        //create new reference
        if(widget_ptr != nullptr) {
            size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
            ref_count++;
            lv_obj_set_user_data(widget_ptr, (void*)ref_count);
        }
    }
    return *this;
};
WidgetContainer& WidgetContainer::operator=(WidgetContainer&& other) {
    //the only time reference counters change is if we point to different widgets,
    //although if this *wasn't* true, the whole assignment operation is a no-op anyway.
    if(widget_ptr != other.widget_ptr) {
        //destroy old reference
        if(widget_ptr != nullptr) {
            size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
            if (ref_count > 1) {
                ref_count--;
                lv_obj_set_user_data(widget_ptr, (void*)ref_count);
            } else {
                lv_obj_clean(widget_ptr);
                lv_obj_delete(widget_ptr);
            }
        }
        //reassign
        widget_ptr = other.widget_ptr;
        //create new reference
        if(widget_ptr != nullptr) {
            size_t ref_count = (size_t)lv_obj_get_user_data(widget_ptr);
            ref_count++;
            lv_obj_set_user_data(widget_ptr, (void*)ref_count);
        }
    }
    return *this;
};

WidgetContainer::WidgetContainer(lv_obj_t* widget) {
    this->widget_ptr = widget;
    //we *should* be the sole owner of this widget at this point.
    //otherwise the constructor is being used incorrectly.
    lv_obj_set_user_data(this->widget_ptr, (void*)1);
}

WidgetContainer& Widget::getParent() {
    return *parent;
}

Widget::Widget(WidgetContainer& parent, lv_obj_t* widget, uint32_t id): WidgetContainer(widget) {
    this->tile = &parent.getTile();
    this->parent = &parent;
    this->id = id;
}

Widget& Widget::addEventCallback(lv_event_cb_t event_cb, lv_event_code_t filter, void *user_data) {
    lv_obj_add_event_cb(this->getWidgetPtr(), event_cb, filter, user_data);
    return *this;
}
Tile& Widget::getTile(){
    return *tile;
}

Label& Widget::addLabel(std::string name){
    return this->getTile().createLabel(*this, name);
}

Widget& Widget::addFlag(lv_obj_flag_t flag) {
    lv_obj_add_flag(this->getWidgetPtr(), flag);
    return *this;
}

Widget& Widget::removeFlag(lv_obj_flag_t flag) {
    lv_obj_remove_flag(this->getWidgetPtr(), flag);
    return *this;
}

Widget& Widget::setPos(int32_t x, int32_t y) {
    lv_obj_set_pos(this->getWidgetPtr(), x, y);
    return *this;
}

Widget& Widget::setX(int32_t x) {
    lv_obj_set_x(this->getWidgetPtr(), x);
    return *this;
}

Widget& Widget::setY(int32_t y) {
    lv_obj_set_y(this->getWidgetPtr(), y);
    return *this;
}

Widget& Widget::setLayout(lv_layout_t layout) {
    lv_obj_set_layout(this->getWidgetPtr(),layout);
    return *this;
}

Widget& Widget::setAlign(lv_align_t align) {
    lv_obj_set_align(this->getWidgetPtr(),align);
    return *this;
}

Widget& Widget::align(lv_align_t align, int32_t x_offset, int32_t y_offset) {
    lv_obj_align(this->getWidgetPtr(), align, x_offset, y_offset);
    return *this;
}

Widget& Widget::alignTo(Widget& base, lv_align_t align, int32_t x_offset, int32_t y_offset) {
    lv_obj_align_to(this->getWidgetPtr(), base.getWidgetPtr(), align, x_offset, y_offset);
    return *this;
}

Widget& Widget::center() {
    lv_obj_center(this->getWidgetPtr());
    return *this;
}

Widget& Widget::setSize(int32_t w, int32_t h) {
    lv_obj_set_size(this->getWidgetPtr(), w, h);
    return *this;
}

Widget& Widget::setWidth(int32_t w) {
    lv_obj_set_width(this->getWidgetPtr(), w);
    return *this;
}

Widget& Widget::setHeight(int32_t h) {
    lv_obj_set_height(this->getWidgetPtr(), h);
    return *this;
}

Widget& Widget::setContentWidth(int32_t w) {
    lv_obj_set_content_width(this->getWidgetPtr(), w);
    return *this;
}

Widget& Widget::setContentHeight(int32_t h) {
    lv_obj_set_content_height(this->getWidgetPtr(), h);
    return *this;
}

Widget& Widget::setFont(const lv_font_t* font, lv_style_selector_t selector) {
    lv_obj_set_style_text_font(this->getWidgetPtr(), font, selector);
    return *this;
}
#include "gui.h"

Popup::~Popup() {}
Popup::Popup(GUI& ctx, lv_obj_t* tile_id): WidgetContainer(tile_id), 
    content(ctx, lv_msgbox_get_content(this->getWidgetPtr()), 0,0) {
}


//Add a new label widget as the child of this widget container
        Container& Popup::addContainer(std::string name) {
            return content.addContainer(name);
        }

        //Add a new label widget as the child of this widget container
        Label& Popup::addLabel(std::string name) {
            return content.addLabel(name);
        }


        //Add a new label widget as the child of this widget container
        Image& Popup::addImage(std::string name) {
            return content.addImage(name);
        }


        //Add a new label widget as the child of this widget container
        Dropdown& Popup::addDropdown(std::string name) {
            return content.addDropdown(name);
        }


        //Add a new label widget as the child of this widget container
        Chart& Popup::addChart(std::string name) {
            return content.addChart(name);
        }

        //Get a reference to the parent tile container
        Tile& Popup::getTile() {
            return content;
        }

        //Get a reference to the parent widget/container
        WidgetContainer& Popup::getParent() {
            return content;
        }

Popup& Popup::addTitle(const std::string& title) {
    auto a = lv_msgbox_add_title(this->getWidgetPtr(), title.c_str());
    lv_obj_set_style_text_font(a, &lv_font_montserrat_44, LV_PART_MAIN);
    lv_obj_set_height(a, 50);
    return *this;
}
Popup& Popup::addButton(const std::string& title) {
    auto a = lv_msgbox_add_footer_button(this->getWidgetPtr(), title.c_str());
    lv_obj_set_style_text_font(a, &lv_font_montserrat_44, LV_PART_MAIN);
    lv_obj_set_height(a, 50);
    return *this;
}
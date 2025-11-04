#ifndef GUI_DROPDOWN_H
#define GUI_DROPDOWN_H
#include "gui.h"

class Dropdown: public Widget {
    public:
    Dropdown(WidgetContainer& parent, uint32_t id);
    ///# Label::setText
    ///
    /// Sets the text attribute of the label to the provided string
    Dropdown& setText(std::string text);

    ///# Dropdown::setOptions
    ///Sets the available options inside the dropdown based 
    ///on a newline-seperated string. 
    Dropdown& setOptions(std::string& text);

    ///# Dropdown::addOption
    ///inserts a new option at index ``pos``
    Dropdown& addOption(std::string& text, uint32_t pos);

    ///# Dropdown::getSelectedItem
    ///get the index of the currently selected item
    uint32_t getSelectedItem();
    
};
#endif
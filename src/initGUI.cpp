#include "initGUI.h"
#include "gui/gui.h"
#include <vector>
#include <unordered_map>

static GUI gui;
void constructUi() {
    
    //init
    gui.init();


    //Main Screen
    Tile& main_screen = gui.addTile();
    
    //project text
    Widget& project_label = main_screen
        .addLabel()
        .setText("PA1484 Software Engineering Project")
        .setFont(&lv_font_montserrat_28)
        .center();
    
    //group number label
    main_screen
        .addLabel()
        .setText("Group 14")
        .setFont(&lv_font_montserrat_44)
        .alignTo(project_label, LV_ALIGN_CENTER, 0, -40);

    Tile& test_screen = gui.addTile();
}


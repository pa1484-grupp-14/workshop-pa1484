#include "initGUI.h"
#include "gui/gui.h"
#include <vector>
#include <unordered_map>

static GUI gui;
void constructUi() {
    
    //init
    gui.init();
    gui.init();
  {
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


    //Second screen
    gui.addTile()
        .addChart()
        .addSeries("main series")
        .addPoints("main series", {20, 40, 30, 50, 60, 5, 10, 99, 80, 0})
        .setSize(300, 300)
        .center();

    //Third Screen
    gui.addTile()
        .setFlexLayout(LV_FLEX_FLOW_ROW, LV_FLEX_ALIGN_SPACE_EVENLY)
        .addLabel()
        .setText("Select one of the options:")
        .getTile()
        .addDropdown()
        .setOptions("First\nSecond\nThird");
  }
}


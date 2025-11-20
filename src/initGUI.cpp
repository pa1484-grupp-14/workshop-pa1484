#include "initGUI.h"

#include <vector>
#include <unordered_map>

        static int32_t columns[] = {300, 300, LV_GRID_TEMPLATE_LAST};
        static int32_t row[] = {120, 70, 70, 70, LV_GRID_TEMPLATE_LAST};


void constructUi() {
    
    //init
    gui.init();


    //Main Screen
    Tile& main_screen = gui.addTile();
    
    //project text
    Widget& project_label = main_screen
        .addLabel()
        .setText("PA1484 Software development project")
        .center();
    
    //group number label
    main_screen
        .addLabel()
        .setText("Group 14")
        .alignTo(project_label, LV_ALIGN_CENTER, 0, -20);

        
        
        //Second screen
        gui.addTile()
            .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY)
            .addLabel().setText("Weather chart").setFont(&lv_font_montserrat_48).getTile()
            .addChart().addSeries("main series").addPoints("main series", {20, 40, 30, 50, 60, 5, 10, 99, 80, 0}).setSize(500, 300);


        //Third Screen
        gui.addTile()
            .setGridLayout(columns, row)
            .addLabel().setText("Settings").setFont(&lv_font_montserrat_48)
            .setGridCell(0, 0, 1, 2).getTile()
            .addLabel().setText("Weather parameter:").setFont(&lv_font_montserrat_26)
            .setGridCell(1, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END).getTile()
            .addDropdown().setOptions("Temperature\nMoisture\nWind").setListFont(&lv_font_montserrat_26).setFont(&lv_font_montserrat_26)
            .setGridCell(1, 1).setWidth(270).getTile()
            .addLabel("Select option 2 ").setText("Weather location:").setFont(&lv_font_montserrat_26)
            .setGridCell(2, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END).getTile()
            .addDropdown().setOptions("Karlskrona\nGothenburg\nStockholm\nMalmo").setListFont(&lv_font_montserrat_26).setFont(&lv_font_montserrat_26)
            .setGridCell(2, 1).setWidth(270).getTile();
    /*
        Tile weather_report = gui.addTile();
        weather_report.setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY);
        */

}


#include "initGUI.h"
#include "gui/gui.h"
#include <vector>
#include <unordered_map>

#include "gui/icons/wi_cloudy.c"
#include "gui/icons/wi_celsius.c"
#include "gui/icons/wi_raindrop.c"

static GUI gui;

WidgetContainer& AddForecastDay(WidgetContainer& tile, const std::string& day, int temp, int moisture, int icon) {
    static int cols[] = { 100, 100, 100, 100, 100, LV_GRID_TEMPLATE_LAST };
    static int rows[] = { 35,40, LV_GRID_TEMPLATE_LAST };
    auto container = tile.addContainer();
    container.setGridLayout(cols, rows).setSize(550, 125);
    container.addImage().setSource(&wi_cloudy).setScale(0.9).setGridCell(0, 0, 2, 1).setSize(100, 80);
    container.addLabel().setText(day).setFont(&lv_font_montserrat_44).setGridCell(0, 1, 1, 4);
    container.addLabel().setText(std::to_string(temp)).setFont(&lv_font_montserrat_28).setGridCell(1, 1,1,1,LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
    container.addImage().setSource(&wi_celsius).setScale(0.8).setGridCell(1, 2, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);
    container.addLabel().setText(std::to_string(moisture) + " mm/h").setFont(&lv_font_montserrat_28).setGridCell(1, 3, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
    container.addImage().setSource(&wi_raindrop).setScale(0.8).setGridCell(1, 4, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);

    return tile;
}

void constructUi() {
    
    //init
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

     //group number label
    main_screen
        .addLabel()
        .setText("Version 2")
        .setFont(&lv_font_montserrat_28)
        .alignTo(project_label, LV_ALIGN_CENTER, 0, 40);



        //Forecast Screen
        Container& weather_forecast = gui.addTile().addContainer();
        weather_forecast.setSize(600, 1000).setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY);

        AddForecastDay(weather_forecast, "Monday",      20, 0, 0);
        AddForecastDay(weather_forecast, "Tuesday",     20, 3, 0);
        AddForecastDay(weather_forecast, "Wednesday",   20, 1, 0);
        AddForecastDay(weather_forecast, "Thursday",    20, 3, 0);
        AddForecastDay(weather_forecast, "Friday",      20, 0, 0);
        AddForecastDay(weather_forecast, "Saturday",    20, 0, 0);
        AddForecastDay(weather_forecast, "Sunday",      20, 0, 0);


        //Second screen
        gui.addTile()
            .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY)
            .addLabel().setText("Weather chart").setFont(&lv_font_montserrat_44).getTile()
            .addChart().addSeries("main series").addPoints("main series", {20, 40, 30, 50, 60, 5, 10, 99, 80, 0}).setSize(500, 300);

        int32_t columns[] = {300, 300, LV_GRID_TEMPLATE_LAST};
        int32_t row[] = {120, 70, 70, 70, LV_GRID_TEMPLATE_LAST};
        //Third Screen
        gui.addTile()
            .setGridLayout(columns, row)
            .addLabel().setText("Settings").setFont(&lv_font_montserrat_44)
            .setGridCell(0, 0, 1, 2).getTile()
            .addLabel().setText("Weather parameter:").setFont(&lv_font_montserrat_28)
            .setGridCell(1, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END).getTile()
            .addDropdown().setOptions("Temperature\nMoisture\nWind").setListFont(&lv_font_montserrat_28).setFont(&lv_font_montserrat_28)
            .setGridCell(1, 1).setWidth(270).getTile()
            .addLabel("Select option 2 ").setText("Weather location:").setFont(&lv_font_montserrat_28)
            .setGridCell(2, 0, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END).getTile()
            .addDropdown().setOptions("Karlskrona\nGothenburg\nStockholm\nMalmo").setListFont(&lv_font_montserrat_28).setFont(&lv_font_montserrat_28)
            .setGridCell(2, 1).setWidth(270).getTile();

        Tile weather_report = gui.addTile();
        weather_report.setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY);
  }
}


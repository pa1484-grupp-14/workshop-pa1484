#include "initGUI.h"
#include "apiLogic/ApiHandling.h"
#include <vector>
#include <unordered_map>


#include "gui/icons/wi_cloudy.c"
#include "gui/icons/wi_celsius.c"
#include "gui/icons/wi_raindrop.c"

#include "gui/icons/wi_day_sunny.c"
#include "gui/icons/wi_day_snow.c"
#include "gui/icons/wi_day_rain.c"
#include "gui/icons/wi_day_showers.c"
#include "gui/icons/wi_day_sleet.c"
#include "gui/icons/wi_day_cloudy.c"
#include "gui/icons/wi_day_thunderstorm.c"
#include "gui/icons/wi_day_sunny_overcast.c"
#include "gui/icons/wi_day_fog.c"
#include "gui/icons/wi_day_sprinkle.c"


static int32_t columns[] = {300, 300, LV_GRID_TEMPLATE_LAST};
static int32_t row[] = {120, 70, 70, 70, LV_GRID_TEMPLATE_LAST};



//Symbol Codes as defined by SMHI API
#define SC_CLEAR_SKY 1
#define SC_NEARLY_CLEAR_SKY 2
#define SC_VARIABLE_CLOUDS 3
#define SC_HALFCLEAR_SKY 4
#define SC_CLOUDY_SKY 5
#define SC_OVERCAST 6
#define SC_FOG 7
#define SC_LIGHT_RAIN_SHOWERS 8
#define SC_MODERATE_RAIN_SHOWERS 9
#define SC_HEAVY_RAIN_SHOWERS 10
#define SC_THUNDERSTORM_SHOWERS 11
#define SC_LIGHT_SLEET_SHOWERS 12
#define SC_MODERATE_SLEET_SHOWERS 13
#define SC_HEAVY_SLEET_SHOWERS 14
#define SC_LIGHT_SNOW_SHOWERS 15
#define SC_MODERATE_SNOW_SHOWERS 16
#define SC_HEAVY_SNOW_SHOWERS 17
#define SC_LIGHT_RAIN 18
#define SC_MODERATE_RAIN 19
#define SC_HEAVY_RAIN 20
#define SC_THUNDER 21
#define SC_LIGHT_SLEET 22
#define SC_MODERATE_SLEET 23
#define SC_HEAVY_SLEET 24
#define SC_LIGHT_SNOW 25
#define SC_MODERATE_SNOW 26
#define SC_HEAVY_SNOW 27


static std::vector<std::string> cities = {"Karlskrona"};

WidgetContainer& AddForecastDay(WidgetContainer& tile, const std::string& day, const std::string& date, int temp, int moisture, int icon) {
    static int cols[] = { 100, 90, 90, 100, 80, LV_GRID_TEMPLATE_LAST };
    static int rows[] = { 35,40, LV_GRID_TEMPLATE_LAST };
    const lv_image_dsc_t* icon_image = &wi_day_sunny;

    switch (icon) {
        case SC_CLEAR_SKY:
            icon_image = &wi_day_sunny;
            break;
        case SC_NEARLY_CLEAR_SKY:
            icon_image = &wi_day_sunny;
            break;
        case SC_VARIABLE_CLOUDS:
            icon_image = &wi_day_sunny_overcast;
            break;
        case SC_HALFCLEAR_SKY:
            icon_image = &wi_day_cloudy;
            break;
        case SC_CLOUDY_SKY:
            icon_image = &wi_cloudy;
            break;
        case SC_OVERCAST:
            icon_image = &wi_day_sunny_overcast;
            break;
        case SC_FOG:
            icon_image = &wi_day_fog;
            break;
        case SC_LIGHT_RAIN_SHOWERS:
            icon_image = &wi_day_sprinkle;
            break;
        case SC_MODERATE_RAIN_SHOWERS:
            icon_image = &wi_day_showers;
            break;
        case SC_HEAVY_RAIN_SHOWERS:
            icon_image = &wi_day_rain;
            break;
        case SC_THUNDERSTORM_SHOWERS:
            icon_image = &wi_day_thunderstorm;
            break;
        case SC_LIGHT_SLEET_SHOWERS:
            icon_image = &wi_day_sprinkle;
            break;
        case SC_MODERATE_SLEET_SHOWERS:
            icon_image = &wi_day_showers;
            break;
        case SC_HEAVY_SLEET_SHOWERS:
            icon_image = &wi_day_sleet;
            break;
        case SC_LIGHT_SNOW_SHOWERS:
            icon_image = &wi_day_sprinkle;
            break;
        case SC_MODERATE_SNOW_SHOWERS:
            icon_image = &wi_day_snow;
            break;
        case SC_HEAVY_SNOW_SHOWERS:
            icon_image = &wi_day_snow;
            break;
        case SC_LIGHT_RAIN:
            icon_image = &wi_day_sprinkle;
            break;
        case SC_MODERATE_RAIN:
            icon_image = &wi_day_showers;
            break;
        case SC_HEAVY_RAIN:
            icon_image = &wi_day_rain;
            break;
        case SC_THUNDER:
            icon_image = &wi_day_thunderstorm;
            break;
        case SC_LIGHT_SLEET:
            icon_image = &wi_day_sprinkle;
            break;
        case SC_MODERATE_SLEET:
            icon_image = &wi_day_showers;
            break;
        case SC_HEAVY_SLEET:
            icon_image = &wi_day_sleet;
            break;
        case SC_LIGHT_SNOW:
            icon_image = &wi_day_sprinkle;
            break;
        case SC_MODERATE_SNOW:
            icon_image = &wi_day_snow;
            break;
        case SC_HEAVY_SNOW:
            icon_image = &wi_day_snow;
            break;
        default:
            icon_image = &wi_cloudy;
            break;
    }

    auto container = tile.addContainer();
    container.setGridLayout(cols, rows).setSize(550, 125);
    container.addImage().setSource(icon_image).setGridCell(0, 0, 2, 1).setSize(100, 80);
    container.addLabel().setText(day).setFont(&lv_font_montserrat_48).setGridCell(0, 1, 1, 3);
    container.addLabel().setText(date).setFont(&lv_font_montserrat_28).setGridCell(0, 4).setSize(100,40);
    container.addLabel().setText(std::to_string(temp)).setFont(&lv_font_montserrat_28).setGridCell(1, 1,1,1,LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
    container.addImage().setSource(&wi_celsius).setGridCell(1, 2, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);
    container.addLabel().setText(std::to_string(moisture) + "%").setFont(&lv_font_montserrat_28).setGridCell(1, 3, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_END);
    container.addImage().setSource(&wi_raindrop).setGridCell(1, 4, 1, 1, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_START);

    return tile;
}

// NOTICE: modified from https://www.geeksforgeeks.org/dsa/find-day-of-the-week-for-a-given-date/ (retrieved 20/11/2025)
// Function to calculate the day of the week using the formula-based approach
int dayOfWeek(int d, int m, int y) {
    // Predefined month codes for each month
    static int monthCode[] = { 5, 1, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3 };

    // Adjust year for January and February
    if (m < 3) {
        y -= 1;  // If month is January or February, treat them as part of the previous year
    }

    // Calculate the year code
    int yearCode = (y % 100) + (y % 100) / 4;

    // Adjust year code for the century
    yearCode = (yearCode + (y / 100) / 4 + 5 * (y / 100)) % 7;

    // Calculate the day of the week and return the value as an integer
    return (d + monthCode[m - 1] + yearCode) % 7;
}

void city_cancel_cb(lv_event_t * event) {
    gui.ClosePopup();
}
void city_picker_cb(lv_event_t * event) {
    gui.OpenPopup().addDropdown().setOptions("Placeholder");
}
void city_dropdown_cb(lv_event_t * event) {
    lv_obj_t* dropdown = (lv_obj_t*)lv_event_get_target(event);
    int selected = lv_dropdown_get_selected(dropdown);
    int len = lv_dropdown_get_option_count(dropdown);
    if(selected == len-1) {
        gui.OpenPopup()
        .addButton("Cancel", city_cancel_cb).addButton("Next", city_picker_cb).getTile().setSize(550, 200)
        .setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_AROUND)
        .addLabel()
        .setText("Add new city...")
        .setFont(&lv_font_montserrat_44)
        .getTile()
        .addLabel()
        .setText("Select the first\nletter of your city.")
        .setFont(&lv_font_montserrat_32).getTile().addDropdown().setOptions("A\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ").setListFont(&lv_font_montserrat_44).setFont(&lv_font_montserrat_44);
        /*
        lv_obj_t* content = lv_msgbox_get_content(popup);
        lv_msgbox_add_title(popup, "Add city...");
        lv_msgbox_add_footer_button(popup, "Cancel");
        lv_msgbox_add_footer_button(popup, "Next");
        lv_obj_t* dropdown = lv_dropdown_create(content);
        lv_dropdown_set_options(dropdown, );
        */
    }
}

void constructUi() {

    //init
    gui.init();


    //Main Screen
    Tile& main_screen = gui.addTile();

    //project text
    Widget& project_label = main_screen
        .addLabel("main label")
        .setText("PA1484 Software development project")
        .setFont(&lv_font_montserrat_28)
        .center();

    //group number label
    main_screen
        .addLabel()
        .setText("Group 14")
        .setFont(&lv_font_montserrat_48)
        .alignTo(project_label, LV_ALIGN_CENTER, 0, -40).focusOn()
        .getTile().addLabel().setText("Version 2").setFont(&lv_font_montserrat_44).alignTo(project_label, LV_ALIGN_CENTER, 0, 150);




    /*
        Tile weather_report = gui.addTile();
        weather_report.setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY);
        */
    APIhandler handler;
  std::unordered_map<std::string, StationObject> stationsArray = handler.getStationsArray(30, 1);
  StationObject station = handler.getStationFromArray(stationsArray, "Karlskrona");
  //Serial.println("name: " + String(station.getName().c_str()) + " longitude: " + String(station.getLon()) + " latitude: " + String(station.getLat()));
  std::vector<ForecastObject> forecasts = handler.getForecastNext7Days(station);


    Container& weather_forecast = gui.addTile().addContainer().disableFrame();
        weather_forecast.setSize(600, 1000).setFlexLayout(LV_FLEX_FLOW_COLUMN, LV_FLEX_ALIGN_SPACE_EVENLY);



        for (size_t i = 0; i < 7; i++){
            ForecastObject& day = forecasts.at(i);
            int year = std::stoi(day.time.substr(0, 4));
            int month = std::stoi(day.time.substr(5, 2));
            int d = std::stoi(day.time.substr(8, 2));
            std::string day_string;
            switch (dayOfWeek(d, month, year)) {
            case 0:
                day_string = "Monday";
                break;
            case 1:
                day_string = "Tuesday";
                break;
            case 2:
                day_string = "Wednesday";
                break;
            case 3:
                day_string = "Thursday";
                break;
            case 4:
                day_string = "Friday";
                break;
            case 5:
                day_string = "Saturday";
                break;
            case 6:
                day_string = "Sunday";
                break;

                default:
                    day_string = "null";
                    break;
            }


            AddForecastDay(weather_forecast, day_string, "("+ day.time.substr(5, 2)+ "/"+ day.time.substr(8, 2)+ ")", day.air_temperature, day.relative_humidity, day.symbol_code);



            }





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
            .addDropdown("cities")
            .setOptions(cities)
            .pushOption("add city...")
            .setListFont(&lv_font_montserrat_26)
            .setFont(&lv_font_montserrat_26)
            .addEventCallback(city_dropdown_cb, LV_EVENT_VALUE_CHANGED, &cities)
            .setGridCell(2, 1).setWidth(270).getTile();

        gui.scrollToTile(0);
}


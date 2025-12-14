#ifdef LILYGO_BUILD
#include <WiFi.h>
#endif
#ifdef NATIVE_BUILD 
#include "nativeReplacements/WiFi.h"
#endif
#include "gui/Gui.h"
#include "components/Components.h"


//These act as application singletons, accessible from anywhere via the get functions.
static GUI gui;
static MainScreen mainScreen;
static Forecast forecastScreen;
static WeatherChart weatherChartScreen;
static Settings settingsScreen;

// Get the GUI of the application
GUI& getGui() {
    return gui;
}
// Get the main screen of the application
MainScreen& getMainScreen() {
    return mainScreen;
}
// Get the forecast screen the application
Forecast& getForecastScreen() {
    return forecastScreen;
}
// Get the weather chart of the application
WeatherChart& getWeatherChartScreen() {
    return weatherChartScreen;
}
// Get the settings of the application
Settings& getSettingsScreen() {
    return settingsScreen;
}

// Create a ui with a loading spinner and status text on the specified tile
void createLoadingUi(Tile* ui_tile, std::string statusText) {
  
    // Cleanse any widgets that may currently be in this ui
    ui_tile->clear(); 
  
    // Add the widgets
    Widget& label = ui_tile->addLabel().setText(statusText);
    Widget& spinner = ui_tile->addSpinner();
  
    // Set the position and attributes of the widgets
    spinner.center().setSize(60, 60);
    label.setFont(&lv_font_montserrat_32)
        .alignTo(spinner, LV_ALIGN_BOTTOM_MID, 0, 50);
}

// Returns true when wifi is connected, false when not
bool is_wifi_connected() {
    #ifdef LILYGO_BUILD
    return WiFi.status() == WL_CONNECTED;
    #elif NATIVE_BUILD
    return true; // i assume your computer has an internet connection
    #endif
}

// When not on the ESP, use system time to replace the millis function
#ifndef LILYGO_BUILD
#include <chrono>
//static containing the start time of the application
static std::chrono::time_point<std::chrono::system_clock> start;
static bool started = false;

unsigned long millis() {
    //set the start time if this is the first time ever using this function
    if(!started) {
        started = true;
        start = std::chrono::system_clock::now();
    }
    
    //get the ellapsed time since the starting time
    auto rightNow = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = rightNow-start;
    
    //convert the difference into milliseconds
    return long(elapsed.count() * 1000.0);
}
#endif
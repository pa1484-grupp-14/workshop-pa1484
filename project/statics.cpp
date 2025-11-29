#include "gui/Gui.h"
#include "components/prelude.h"

static GUI gui;
static MainScreen mainScreen;
static Forecast forecastScreen;
static WeatherChart weatherChartScreen;
static Settings settingsScreen;


GUI& getGui() {
    return gui;
}
MainScreen& getMainScreen() {
    return mainScreen;
}
Forecast& getForecastScreen() {
    return forecastScreen;
}
WeatherChart& getWeatherChartScreen() {
    return weatherChartScreen;
}
Settings& getSettingsScreen() {
    return settingsScreen;
}
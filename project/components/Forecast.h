#pragma once

#include <lvgl.h>
#include "gui/Gui.h"
#include "apiLogic/ApiHandling.h"


enum ForecastStatus {
    WaitingForWifi = 0,
    FetchingStations,
    FetchingForecast,
    Fetched,
    FailedFetch,
};


class Forecast : public Component {
    private:
        Tile* uiTile;
        ForecastObject forecastData[7];
        ForecastStatus status;

        std::string currentCity;

    public:
    Forecast();
    ~Forecast();
    void constructUI(Tile *gui) override;

    void switchToForecastScreen(std::vector<ForecastObject>& forecasts);
    void switchToLoadingForecasts(std::unordered_map<std::string, StationObject>& stationArray);
    void switchToLoadingStations();
    void switchToFailScreen();

    //perform full refresh
    void refresh();
    //only refresh weather parameters
    void refreshWeatherParameter();
    
    void process() override;
};

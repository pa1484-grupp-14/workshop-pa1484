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
        Tile* ui_tile;
        ForecastObject forecast_data[7];
        ForecastStatus status;

        std::optional<StationObject> current_station;

    public:
    Forecast();
    ~Forecast();
    void constructUI(Tile *gui) override;

    void switchToLoadingScreenStations(std::unordered_map<std::string, StationObject>& stationArray);
    void switchToFailScreen();
    void switchToForecastScreen(std::vector<ForecastObject>& forecasts);
    void switchToLoadingScreen();

    void reset();
    void refreshWeatherParameter();
    

    void process() override;
};

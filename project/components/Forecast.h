#pragma once

#include <lvgl.h>
#include "gui/Gui.h"
#include "apiLogic/ApiHandling.h"


enum ForecastStatus {
    WaitingForWifi = 0,
    Fetching,
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

    void switchToForecastScreen(std::vector<ForecastObject>& forecasts);
    void switchToLoadingScreen();

    void reset();
    

    void process() override;
};

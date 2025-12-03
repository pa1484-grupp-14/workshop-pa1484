#pragma once

#include <lvgl.h>
#include "gui/Gui.h"
#include "apiLogic/ApiHandling.h"


enum ForecastStatus {
    //DEFAULT: currently waiting for wifi
    WaitingForWifi = 0,

    // Waiting for the current forecast fetch to finish
    Fetching,
    
    // Forecast data is fetched and shown
    Fetched,

    // Forecast data failed to be fetched and the user needs to refresh
    FailedFetch,
};

class Forecast : public Component {
    private:
        // Pointer to the UI tile this component owns (used when updating the GUI)
        Tile* ui_tile;

        // Pointer to the forecast days currently being displayed
        ForecastObject forecast_data[7];

        // The current status of the Forecast Screen
        ForecastStatus status;

        // The current station which the forecast data came from
        std::optional<StationObject> current_station;

        // functions used inside the tile to switch between different statuses
        void switchToForecastScreen(std::vector<ForecastObject>& forecasts);
        void switchToLoadingScreen();

    public:
        // Constructor/Destructor
        Forecast();
        ~Forecast();


        // Construct the initial UI (i.e waiting for wifi screen)
        void constructUI(Tile *gui) override;

        // Completely restart the tile and let it re-fetch all data
        void reset();
        
        // Standard component processing
        void process() override;
};

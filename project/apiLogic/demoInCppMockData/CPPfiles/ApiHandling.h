#pragma once
#include <string> 
#include <vector>
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"


class APIhandler
{
public:
    std::vector<StationObject> getSationsArray(int parameter);
    StationObject getStationFromArray(const std::vector<StationObject>& array,const std::string& stationName);
    std::vector<HistoricalObject> getHistoricalData(const std::string& key,int parameter);
    std::vector<ForecastObject> getForecastNext7Days(const StationObject& stationObject);
};

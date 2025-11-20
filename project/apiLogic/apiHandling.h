#pragma once
#include <string> 
#include <vector>
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"


class APIhandler
{
public:
    vector<StationObject> getStationsArray(int citiesAmount , int parameter);
    StationObject getStationFromArray(const vector<StationObject>& array,const string& stationName); 
    std::vector<HistoricalObject> getHistoricalData(const string& key,int parameter);
    std::vector<ForecastObject> getForecastNext7Days(const StationObject& stationObject);
};

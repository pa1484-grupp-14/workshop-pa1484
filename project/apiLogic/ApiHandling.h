#pragma once
#include <string> 
#include <vector>
#include <unordered_map>
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"


class APIhandler
{
public:
    std::unordered_map<std::string, int> getStationsArray(int citiesAmount , int parameter);
    StationObject getStationFromArray(const std::unordered_map<std::string, int>& array,const string& stationName); 
    std::vector<HistoricalObject> getHistoricalData(const string& key,int parameter);
    std::vector<ForecastObject> getForecastNext7Days(const StationObject& stationObject);
};

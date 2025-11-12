#pragma once
#include <string> 
#include <vector>
#include <fstream>
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"

using namespace std;

class APIhandler
{
public:
    vector<StationObject> getSationsArray(int parameter);
    StationObject getStationFromArray(vector<StationObject> array, string stationName);
    vector<HistoricalObject> getHistoricalData(string key, int parameter);
    vector<ForecastObject> getForecastNext7Days(StationObject stationObject); 
};
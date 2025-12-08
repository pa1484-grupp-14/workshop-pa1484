#pragma once
#include <string> 
#include <vector>
#include <unordered_map>
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"

#include "forecastJsonParser.h" 
#include "parameterJsonParser.h"

#include <JsonListener.h>
#include <JsonStreamingParser.h>
#include <HTTPClient.h> 

class StationRequest {
    public:
    int parameter;
    WiFiClient client;
    HTTPClient http;
    JsonStreamingParser parser;
    StationParser listener;
    std::vector<void(*)(std::unordered_map<std::string, StationObject>&)> success_cbs;
    std::vector<void(*)()> failure_cbs;
};
class ForecastRequest {
    public:
    WiFiClient client;
    HTTPClient http;
    JsonStreamingParser parser;
    ForecastListener listener;
    void(*success_cb)(std::vector<ForecastObject>&);
    void(*failure_cb)();
};
class APIhandler
{

    private:


    //background forecasts
    static StationRequest* stationFetch;
    static ForecastRequest* forecastFetch;
    //Forecast which has already been fetched, derived from station name
    static std::unordered_map<std::string, std::vector<ForecastObject>> cached_forecasts;
    //parameter of the cached stations
    static int cached_parameter;
    //cached stations, derived from city name
    static std::unordered_map<std::string, StationObject> cached_stations;
    
    
    
    public:
    static void process();
    std::unordered_map<std::string, StationObject> getStationsArray(int parameter);
    void getStationsArrayAsync(int parameter, void(*success_cb)(std::unordered_map<std::string, StationObject>&), void(*failure_cb)());
    StationObject getStationFromArray(const std::unordered_map<std::string, StationObject>& array,const string& stationName); 
    std::vector<HistoricalObject> getHistoricalData(const string& key,int parameter);
    std::vector<ForecastObject> getForecastNext7Days(const StationObject& stationObject);

    void getForecastNext7DaysAsync(const StationObject& stationObject, void(*success_cb)(std::vector<ForecastObject>&), void(*failure_cb)());
};

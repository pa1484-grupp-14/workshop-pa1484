#pragma once
#include <string> 
#include <vector>
#include <unordered_map>
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"

#include "forecastJsonParser.h" 
#include "parameterJsonParser.h"
#include "HistoricalListener.h"

#ifdef LILYGO_BUILD
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#include <HTTPClient.h>
#else
#include "nativeReplacements/JsonListener.h"
#include "nativeReplacements/JsonStreamingParser.h"
#include "nativeReplacements/HTTPClient.h"
#include "nativeReplacements/String.h"
#endif

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
class HistoricRequest {
    public:
    WiFiClient client;
    HTTPClient http;
    JsonStreamingParser parser;
    HistoricalListener listener;
    void(*success_cb)(std::vector<HistoricalObject>&);
    void(*failure_cb)();
    int read_bytes;
};
class APIhandler
{

    private:


    std::vector<HistoricalObject> averageByDay(const vector<HistoricalObject>& raw);
    //background forecasts
    static StationRequest* stationFetch;
    static ForecastRequest* forecastFetch;
    static HistoricRequest* historyFetch;
    //Forecast which has already been fetched, derived from station name
    static std::unordered_map<std::string, std::vector<ForecastObject>> cached_forecasts;
    //parameter of the cached stations
    static int cached_parameter;
    //cached stations, derived from city name
    static std::unordered_map<std::string, StationObject> cached_stations;
    
    public:
    static void process();
    
    StationObject getStationFromArray(const std::unordered_map<std::string, StationObject>& array,const string& stationName); 
    
    std::unordered_map<std::string, StationObject> getStationsArray(int parameter);
    std::vector<HistoricalObject> getHistoricalData(const StationObject& station, int parameter);
    std::vector<ForecastObject> getForecastNext7Days(const StationObject& stationObject);

    void getStationsArrayAsync(int parameter, void(*success_cb)(std::unordered_map<std::string, StationObject>&), void(*failure_cb)());
    void getForecastNext7DaysAsync(const StationObject& stationObject, void(*success_cb)(std::vector<ForecastObject>&), void(*failure_cb)());
    void getHistoricalDataAsync(const StationObject& station, int parameter, void(*success_cb)(std::vector<HistoricalObject>&), void(*failure_cb)());
    
};

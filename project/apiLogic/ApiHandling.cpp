#include "ApiHandling.h"

#include "StationObject.h"
#include "ForecastObject.h"
#include "forecastJsonParser.h" 
#include "parameterJsonParser.h"
#include <iostream>
#include <ArduinoJson.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstring>

#ifdef LILYGO_BUILD
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#include <HTTPClient.h> 
#endif
#ifdef NATIVE_BUILD
#include "nativeReplacements/JsonListener.h"
#include "nativeReplacements/JsonStreamingParser.h"
#include "nativeReplacements/HTTPClient.h"
#endif


std::unordered_map<std::string, std::vector<ForecastObject>> APIhandler::cached_forecasts = std::unordered_map<std::string, std::vector<ForecastObject>>();
int APIhandler::cached_parameter = 0;
std::unordered_map<std::string, StationObject> APIhandler::cached_stations = {};

StationObject APIhandler::getStationFromArray(const std::unordered_map<std::string, StationObject>& array, const std::string& stationName) 
{
    return array.at(stationName);
}

vector<HistoricalObject> APIhandler::getHistoricalData(const string& key, int parameter)
{
   



    

    return vector<HistoricalObject>();
}
void APIhandler::getForecastNext7DaysAsync(const StationObject& stationObject, void(*success_cb)(std::vector<ForecastObject>&), void(*failure_cb)()) {
    if(forecastFetch != nullptr) {
        forecastFetch->http.end();
        delete forecastFetch;
        forecastFetch == nullptr;
    }
    
    ForecastRequest* fetch = new ForecastRequest{WiFiClient(), HTTPClient(), JsonStreamingParser(), ForecastListener(), success_cb, failure_cb};
    float lon = stationObject.getLon();
    float lat = stationObject.getLat();
    String url = "http://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon/";
    url += String(lon) + "/" +"lat/" + String(lat) + "/data.json";
    fetch->client.setTimeout(1);
    if (fetch->http.begin(fetch->client, url)) {
        int code = fetch->http.GET();
        if (code == HTTP_CODE_OK) {
            fetch->parser.setListener(&fetch->listener);
            std::cout << "[APIHandler]: Fetching forecast asynchronously!." << std::endl;
            forecastFetch = fetch;
        }
        else
        {
            fetch->http.end();
            if(failure_cb) {
                failure_cb();
            }   
            delete fetch;
            std::cout << "[APIHandler]: Failed to fetch forecast" << std::endl;
        }
    }
}
std::vector<ForecastObject> APIhandler::getForecastNext7Days(const StationObject& stationObject)
{
    /*
    if(cached_forecasts.count(stationObject.getName()) > 0) {
        std::cout << "[APIHandler]: returning cached forecast instead." << std::endl;
        return cached_forecasts.at(stationObject.getName());
    }
        */
    float lon = stationObject.getLon();
    float lat = stationObject.getLat();
    String url = "http://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon/";
    url += String(lon) + "/" +"lat/" + String(lat) + "/data.json";
    
    // Your Domain name with URL path or IP address with path   
    WiFiClient client;
    HTTPClient http;
    JsonStreamingParser parser;
    ForecastListener listener;

    // If your need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

    if (http.begin(client, url)) {

        int code = http.GET();
        if (code == HTTP_CODE_OK) {

            // Get stream
            WiFiClient * stream = http.getStreamPtr();

            // Initialize your streaming parser
            parser.setListener(&listener);

            // Read response in chunks
            const int BUFFER_SIZE = 512;
            uint8_t buffer[BUFFER_SIZE];
   
            auto before = millis();
            while ((stream->connected() || stream->available()) && listener.itemCount != 7) {
                int len = stream->readBytes(buffer, BUFFER_SIZE);
                for (int i = 0; i < len; i++) {
                    parser.parse((char)buffer[i]);
                }
            }
            auto after = millis();
            std::cout << "[APIHandler]: took " << after-before << "ms to parse all statsions." << std::endl;
        }
        else
        {
            std::cout << "Failed to fetch" << std::endl;
            return vector<ForecastObject>();
        }
           
            

        http.end();
    }
    //cached_forecasts.emplace(stationObject.getName(), listener.forecasts);
    return listener.forecasts;
}
    
 StationRequest* APIhandler::stationFetch = nullptr;
 ForecastRequest* APIhandler::forecastFetch = nullptr;
void APIhandler::getStationsArrayAsync(int parameter, void(*success_cb)(std::unordered_map<std::string, StationObject>&), void(*failure_cb)()) {
    if(parameter == cached_parameter && cached_stations.size() > 0) {
        std::cout << "[APIHandler]: returning cached stations instead." << std::endl;
        success_cb(cached_stations);
    } else {
        if(stationFetch != nullptr) {
            stationFetch->success_cbs.push_back(success_cb);
        } else {
            StationRequest* fetch = new StationRequest{parameter, WiFiClient(), HTTPClient(), JsonStreamingParser(), StationParser(), {success_cb}, {failure_cb}};
            String url = "http://opendata-download-metobs.smhi.se/api/version/latest/parameter/";
            url += String(parameter) + ".json";
            fetch->client.setTimeout(1);
            
            if (fetch->http.begin(fetch->client, url)) {

                int code = fetch->http.GET();
                if (code == HTTP_CODE_OK) {
                    fetch->parser.setListener(&fetch->listener);
                    std::cout << "[APIHandler]: Fetching stations asynchronously!." << std::endl;
                    stationFetch = fetch;
                }
                else
                {
                    fetch->http.end();
                    if(failure_cb) {
                        failure_cb();
                    }   
                    delete fetch;
                    std::cout << "Failed to fetch station keys and cities" << std::endl;
                }
            }
        }
    }
}
std::unordered_map<std::string, StationObject> APIhandler::getStationsArray(int parameter)    
{
    if(parameter == cached_parameter && cached_stations.size() > 0) {
        std::cout << "[APIHandler]: returning cached stations instead." << std::endl;
        return cached_stations;
    }
    

    WiFiClient client;
    HTTPClient http;
    JsonStreamingParser parser;
    StationParser listener;
    String url = "http://opendata-download-metobs.smhi.se/api/version/latest/parameter/";
    url += String(parameter) + ".json";

    
    if (http.begin(client, url)) {

        int code = http.GET();
        if (code == HTTP_CODE_OK) {

            // Get stream
            WiFiClient * stream = http.getStreamPtr();

            // Initialize your streaming parser
            parser.setListener(&listener);

            // Read response in chunks
            const int BUFFER_SIZE = 512;
            uint8_t buffer[BUFFER_SIZE];
   
            auto before = millis();
            while ((stream->connected() || stream->available())) {
                int len = stream->readBytes(buffer, BUFFER_SIZE);
                for (int i = 0; i < len; i++) {
                    parser.parse((char)buffer[i]);
                }
            }
            auto after = millis();
            std::cout << "[APIHandler]: took " << after-before << "ms to parse all forecast days." << std::endl;
        }
        else
        {
            std::cout << "Failed to fetch station keys and cities" << std::endl;
            return std::unordered_map<std::string, StationObject>();
        }

        http.end();
    }
    cached_parameter = parameter;
    cached_stations.empty();
    for(auto& station : listener.stations) {
        cached_stations.emplace(station.first, station.second);
    }
    return listener.stations;
}

void APIhandler::process() {
    const int BUFFER_SIZE = 1024;
    if(stationFetch != nullptr) {
        //NOTE: return nullptr when connection is closed, so doubled up as connection status
        WiFiClient * stream = stationFetch->http.getStreamPtr();
        if(stream) {
            //create a chunk
            char buffer[BUFFER_SIZE];
            //fetch and parse it
            auto available = stream->available();
            if(available > 0) {
                int len = stream->readBytes(buffer, min(BUFFER_SIZE, available));
                for (int i = 0; i < len; i++) {
                    stationFetch->parser.parse(buffer[i]);
                }
            }
        } else {
            //assume success when the connection closes
            stationFetch->http.end();
            cached_parameter = stationFetch->parameter;
            cached_stations.empty();
            for(auto& station : stationFetch->listener.stations) {
                cached_stations.emplace(station.first, station.second);
            }
            for(auto& fnPtr : stationFetch->success_cbs) {
                fnPtr(cached_stations);
            }
            delete stationFetch;
            stationFetch = nullptr;    
        }
    }
    if(forecastFetch != nullptr) {
        //NOTE: return nullptr when connection is closed, so doubled up as connection status
        WiFiClient * stream = forecastFetch->http.getStreamPtr();
        if(stream) {
            //create a chunk
            char buffer[BUFFER_SIZE];
            //fetch and parse it
            auto available = stream->available();
            if(available > 0) {
                int len = stream->readBytes(buffer, min(BUFFER_SIZE, available));
                for (int i = 0; i < len; i++) {
                    forecastFetch->parser.parse(buffer[i]);
                }
            }
        } else {
            //assume success when the connection closes
            forecastFetch->http.end();
            forecastFetch->success_cb(forecastFetch->listener.forecasts);
            delete forecastFetch;
            forecastFetch = nullptr;
        }
          
    }
}
#include "ApiHandling.h"
#include "parameterJsonParser.h"
#include "StationObject.h"
#include "ForecastObject.h"
#include "forecastJsonParser.h" 

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
StationObject APIhandler::getStationFromArray(const std::unordered_map<std::string, StationObject>& array, const std::string& stationName) 
{
    return array.at(stationName);
}

vector<HistoricalObject> APIhandler::getHistoricalData(const string& key, int parameter)
{
   



    

    return vector<HistoricalObject>();
}

std::vector<ForecastObject> APIhandler::getForecastNext7Days(const StationObject& stationObject)
{
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
    
    return listener.forecasts;
}



std::unordered_map<std::string, StationObject> APIhandler::getStationsArray(int parameter)    
{

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
    return listener.stations;
}
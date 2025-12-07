
#include "ApiHandling.h"
#include "parameterJsonParser.h"
#include "StationObject.h"
#include "ForecastObject.h"
#include "forecastJsonParser.h"
#include "HistoricalListener.h" 


#include <ArduinoJson.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <map>
#include <HTTPClient.h> 
#include <JsonListener.h>
#include <JsonStreamingParser.h>
 
StationObject APIhandler::getStationFromArray(const std::unordered_map<std::string, StationObject>& array, const std::string& stationName) 
{
    return array.at(stationName);
}

std::vector<HistoricalObject> APIhandler::getHistoricalData(const string& key, int parameter)
{

    return vector<HistoricalObject>();
}

/*
This is a helper function that...
*/
std::vector<HistoricalObject> APIhandler::averageByDay(const vector<HistoricalObject>& raw)
{
    std::map<std::string, std::vector<float>> grouped;

    for (const auto& obj : raw) {
        grouped[obj.getDate()].push_back(obj.getValue());
    }

    std::vector<HistoricalObject> averagedResults;

    for (const auto& entry : grouped) {
        const std::string& date = entry.first;
        const std::vector<float>& values = entry.second;

        float sum = 0;
        for (float v : values) {
            sum += v;
        }

        float avg = sum / values.size();

    }
    return averagedResults;
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
   
            while ((stream->connected() || stream->available()) && listener.itemCount != 7) {
                int len = stream->readBytes(buffer, BUFFER_SIZE);
                for (int i = 0; i < len; i++) {
                    parser.parse((char)buffer[i]);
                }
            }
        }
        else
        {
            Serial.println("Failed to fetch");
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
    String url = "http://opendata-download-metobs.smhi.se/api/version/latest/parameter/" + String(parameter) + ".json";

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
   
            while ((stream->connected() || stream->available())) {
                int len = stream->readBytes(buffer, BUFFER_SIZE);
                for (int i = 0; i < len; i++) {
                    parser.parse((char)buffer[i]);
                }
            }
        }
        else
        {
            Serial.println("Failed to fetch station keys and cities");
            return std::unordered_map<std::string, StationObject>();
        }

        http.end();
    }
    return listener.stations;
}


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
    string url = "https://opendata-download-metobs.smhi.se/api/version/1.0/parameter/"+to_string(parameter) +"/station/"+ key +"/period/latest-months/data.json";

    WiFiClient client;
    HTTPClient http;

    http.begin(client, url.c_str());
    int httpCode = http.GET();

    if (httpCode != 200) {
        return vector<HistoricalObject>();
    }

    HistoricalListener listener;
    JsonStreamingParser parser;
    parser.setListener(&listener);

    WiFiClient* stream = http.getStreamPtr();
    while (stream->connected() || stream->available()) {
        char c = stream->read();
        parser.parse(c);
    }

    http.end();

    vector<HistoricalObject> rawResults = listener.getResults();

    if(listener.isVersion2Data()){
        return rawResults;
    }

    return averageByDay(rawResults);
}


/*
This is a helper function that gets the average per day
*/
std::vector<HistoricalObject> APIhandler::averageByDay(const vector<HistoricalObject>& raw)
{
    std::map<std::string, std::vector<float>> grouped;

    // Group values by their date
    for (const auto& obj : raw) {
        grouped[obj.getDate()].push_back(obj.getValue());
    }

    // Will hold the averaged results
    std::vector<HistoricalObject> averagedResults;

    // Iterates through each date >> list of values
    for (const auto& entry : grouped) {
        const std::string& date = entry.first;
        const std::vector<float>& values = entry.second;

        // Computes the sum of values for the date
        float sum = 0;
        for (float v : values) {
            sum += v;
        }

        // Computes the average
        float avg = sum / values.size();

        // ? Push the averaged HistoricalObject into the output vector
        averagedResults.emplace_back(date, avg);
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

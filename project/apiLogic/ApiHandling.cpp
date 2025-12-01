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
   
            while ((stream->connected() || stream->available()) && listener.itemCount != 7) {
                int len = stream->readBytes(buffer, BUFFER_SIZE);
                for (int i = 0; i < len; i++) {
                    parser.parse((char)buffer[i]);
                }
            }
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
   
            while ((stream->connected() || stream->available())) {
                int len = stream->readBytes(buffer, BUFFER_SIZE);
                for (int i = 0; i < len; i++) {
                    parser.parse((char)buffer[i]);
                }
            }
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

/*
#include "ApiHandling.h"

#include <ArduinoJson.h>
#include <iostream>

#ifdef LILYGO_BUILD
#include <HTTPClient.h>
#else
#include "nativeReplacements/HTTPClient.h"
#endif 

std::string extractCityName(const std::string& stationName) {
    int a = stationName.find("-");
    int b = stationName.find(" ");
    if(a < 0 && b < 0) {
        return stationName;
    } else if (b < 0) {
        return stationName.substr(0,a);
    } else if (a < 0) {
        return stationName.substr(0,b);
    } else {
        return stationName.substr(0,min(a,b));
    }
}
 
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
    std::cout << "[APIHandler]: Starting to fetch forecast data for the current station." << std::endl;
    float lon = stationObject.getLon();
    float lat = stationObject.getLat();
    String url = "http://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon/";
    url += String(lon) + "/" +"lat/" + String(lat) + "/data.json";
    
    // Your Domain name with URL path or IP address with path   
    WiFiClient client;
    HTTPClient http;
    vector<ForecastObject> vector;
    //JsonStreamingParser parser;
    //ForecastListener listener;

    // If your need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

    if (http.begin(client, url)) {

        int code = http.GET();
        if (code == HTTP_CODE_OK) {

            // Get stream
            WiFiClient& stream = *http.getStreamPtr();
            //create a filter document so we only get our wanted fields
            JsonDocument filter;
            
            
            JsonDocument doc;
            DeserializationError result = DeserializationError::IncompleteInput;
            //Since were fetching from a stream it might timeout, so this loop fetches every "chunk" until were finished or an error occurs.
            while(result == DeserializationError::IncompleteInput) {
                //deserialize the request
                auto before = millis();
                result = deserializeJson(doc, stream);
                auto after = millis();
                std::cout << "[APIHandler]: One fetch cycle complete, took " << after-before << "ms" << std::endl;
            }
            switch(result.code()) {
                case DeserializationError::Ok:
                {
                    JsonArray samples = doc["timeSeries"];

                    std::cout << "[APIHandler]: Fetched " << samples.size() << " samples." << std::endl;
                    //get the samples and prepare vector
                    
                    vector.reserve(7);

                    auto before = millis();
                    //search through each sample
                    for(const auto& sample : samples) {
                        //if the sample isn't at 12:00, skip it
                        if(std::string(sample["time"]).substr(11,8) != "12:00:00") continue;

                        //big ugly constructor code
                        const auto& data = sample["data"];
                        ForecastObject forecastDay = {
                            .time = sample["time"],
                            .air_pressure_at_mean_sea_level = data["air_pressure_at_mean_sea_level"],
                            .air_temperature = data["air_temperature"],
                            .cloud_area_fraction = data["cloud_area_fraction"],
                            .cloud_base_altitude = data["cloud_base_altitude"],
                            .cloud_top_altitude = data["cloud_top_altitude"],
                            .high_type_cloud_area_fraction = data["high_type_cloud_area_fraction"],
                            .low_type_cloud_area_fraction = data["low_type_cloud_area_fraction"],
                            .medium_type_cloud_area_fraction = data["medium_type_cloud_area_fraction"],
                            .precipitation_amount_max = data["precipitation_amount_max"],
                            .precipitation_amount_mean = data["precipitation_amount_mean"],
                            .precipitation_amount_median = data["precipitation_amount_median"],
                            .precipitation_amount_min = data["precipitation_amount_min"],
                            .precipitation_frozen_part = data["precipitation_frozen_part"],
                            .predominant_precipitation_type_at_surface = data["predominant_precipitation_type_at_surface"],
                            .probability_of_frozen_precipitation = data["probability_of_frozen_precipitation"],
                            .probability_of_precipitation = data["probability_of_precipitation"],
                            .relative_humidity = data["relative_humidity"],
                            .symbol_code = data["symbol_code"],
                            .thunderstorm_probability = data["thunderstorm_probability"],
                            .visibility_in_air = data["visibility_in_air"],
                            .wind_from_direction = data["wind_from_direction"],
                            .wind_speed = data["wind_speed"],
                            .wind_speed_of_gust = data["wind_speed_of_gust"],
                        };
                        //push the forecast object to the vector
                        vector.push_back(forecastDay);
                        //if our forecast is finished, prematurely break the loop
                        if(vector.size() >= 7) break;
                    }
                    auto after = millis();
                    std::cout << "[APIHandler]: Took " << after-before << "ms to filter all the forecast data" << std::endl;
                    
                }
                    break;
                default:
                    std::cout << "[APIHandler]: An error occured while parsing the response data for stations fetch";
                    break;
            }

        }
        else
        {
            std::cout << "[APIHandler]: Failed to fetch weather forecast";
        }
        http.end();
    }
    
    return vector;
}



std::unordered_map<std::string, StationObject> APIhandler::getStationsArray(int parameter)    
{

    std::cout << "[APIHandler]: Starting to fetch all the weather stations." << std::endl;
    WiFiClient client;
    HTTPClient http;
    //JsonStreamingParser parser;
    //StationParser listener;
    String url = "http://opendata-download-metobs.smhi.se/api/version/latest/parameter/";
    url += String(parameter) + ".json";

    std::unordered_map<std::string, StationObject> hashmap;

    if (http.begin(client, url)) {

        int code = http.GET();
        if (code == HTTP_CODE_OK) {

            // Get stream
            WiFiClient& stream = *http.getStreamPtr();

            //create a filter document so we only get our wanted fields
            JsonDocument filter;
            filter["station"][0]["key"] = true;
            filter["station"][0]["name"] = true;
            filter["station"][0]["latitude"] = true;
            filter["station"][0]["longitude"] = true;

            
            JsonDocument doc;
            DeserializationError result = DeserializationError::IncompleteInput;
            
            //Since were fetching from a stream it might timeout, so this loop fetches every "chunk" until were finished or an error occurs.
            while(result == DeserializationError::IncompleteInput) {
                //deserialize the request
                auto before = millis();
                result = deserializeJson(doc, stream);
                auto after = millis();
                std::cout << "[APIHandler]: One fetch cycle complete, took " << after-before << "ms" << std::endl;
            }
            //act on the result
            switch(result.code()) {
                case DeserializationError::Ok:
                {
                    //get the stations array from document and prepare hashmap
                    JsonArray stations = doc["station"];
                    std::cout << "[APIHandler]: Fetched " << stations.size() << " stations." << std::endl;
                 
                    auto before = millis();
                    hashmap.reserve(stations.size());
                    for(const auto& station : stations) {
                        //construct station objects and place in the hashmap
                        std::string city = extractCityName(station["name"]);
                        StationObject obj = {station["key"], station["name"], station["longitude"], station["latitude"]};
                        hashmap.emplace(city, obj);
                    }
                    auto after = millis();
                    std::cout << "[APIHandler]: Took " << after-before << "ms to insert everything into the hashmap" << std::endl;
                }
                    break;
                default:
                    std::cout << "[APIHandler]: An error occured while parsing the response data for stations fetch (RESULT: " << result << ")" << std::endl;
                    break;
            }
        }
        else
        {
            std::cout << "[APIHandler]: Failed to fetch station keys and cities (HTTP CODE: " << code << ")" << std::endl;
        }

        http.end();
    }
    return hashmap;
}
*/
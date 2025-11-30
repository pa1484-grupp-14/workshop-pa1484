
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
            /*
            filter["timeSeries"][0]["time"] = true;
            filter["timeSeries"][0]["data"]["air_temperature"] = true;
            filter["timeSeries"][0]["data"]["wind_from_direction"] = true;
            filter["timeSeries"][0]["data"]["wind_speed"] = true;
            filter["timeSeries"][0]["data"]["wind_speed_of_gust"] = true;
            filter["timeSeries"][0]["data"]["relative_humidity"] = true;
            filter["timeSeries"][0]["data"]["air_pressure_at_mean_sea_level"] = true;
            filter["timeSeries"][0]["data"]["visibility_in_air"] = true;
            filter["timeSeries"][0]["data"]["thunderstorm_probability"] = true;
            filter["timeSeries"][0]["data"]["probability_of_frozen_precipitation"] = true;
            filter["timeSeries"][0]["data"]["cloud_area_fraction"] = true;
            filter["timeSeries"][0]["data"]["low_type_cloud_area_fraction"] = true;
            filter["timeSeries"][0]["data"]["medium_type_cloud_area_fraction"] = true;
            filter["timeSeries"][0]["data"]["high_type_cloud_area_fraction"] = true;
            filter["timeSeries"][0]["data"]["cloud_base_altitude"] = true;
            filter["timeSeries"][0]["data"]["cloud_top_altitude"] = true;
            filter["timeSeries"][0]["data"]["mtpr"] = true;
            filter["timeSeries"][0]["data"]["precipitation_amount_mean"] = true;
            filter["timeSeries"][0]["data"]["precipitation_amount_min"] = true;
            filter["timeSeries"][0]["data"]["precipitation_amount_max"] = true;
            filter["timeSeries"][0]["data"]["precipitation_amount_median"] = true;
            filter["timeSeries"][0]["data"]["probability_of_precipitation"] = true;
            filter["timeSeries"][0]["data"]["precipitation_frozen_part"] = true;
            filter["timeSeries"][0]["data"]["predominant_precipitation_type_at_surface"] = true;
            filter["timeSeries"][0]["data"]["symbol_code"] = true;
            */
            
            JsonDocument doc;
            DeserializationError result = DeserializationError::IncompleteInput;
            //Since were fetching from a stream it might timeout, so this loop fetches every "chunk" until were finished or an error occurs.
            while(result == DeserializationError::IncompleteInput) {
                //deserialize the request
                result = deserializeJson(doc, stream);
            }
            switch(result.code()) {
                case DeserializationError::Ok:
                {
                    //get the samples and prepare vector
                    JsonArray samples = doc["timeSeries"];
                    vector.reserve(7);

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
                    
                }
                default:
                    std::cout << "[APIHandler]: An error occured while parsing the response data for stations fetch";
                    break;
            }
            /*
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
            }*/

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
                result = deserializeJson(doc, stream, DeserializationOption::Filter(filter));
            }
            //act on the result
            switch(result.code()) {
                case DeserializationError::Ok:
                {
                    //get the stations array from document and prepare hashmap
                    JsonArray stations = doc["station"];
                    hashmap.reserve(stations.size());
                    for(const auto& station : stations) {
                        //construct station objects and place in the hashmap
                        std::string city = extractCityName(station["name"]);
                        StationObject obj = {station["key"], station["name"], station["longitude"], station["latitude"]};
                        hashmap.emplace(city, obj);
                    }
                    
                }
                default:
                    std::cout << "[APIHandler]: An error occured while parsing the response data for stations fetch";
                    break;
            }
        }
        else
        {
            std::cout << "[APIHandler]: Failed to fetch station keys and cities";
        }

        http.end();
    }
    return hashmap;
}

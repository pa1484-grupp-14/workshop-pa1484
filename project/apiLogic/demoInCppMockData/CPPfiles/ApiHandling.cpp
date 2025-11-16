
#include "ApiHandling.h"
#include "StationObject.h"
#include "ForecastObject.h"

#include <ArduinoJson.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstring>

static std::string loadFileToString(const std::string& path)
{
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) throw std::runtime_error("Kunde inte öppna JSON-fil: " + path);
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

vector<StationObject> APIhandler::getStationsArray(int parameter)
{
    const std::string filePath = "./apiLogic/demoInCppMockData/JsonFiles/parameterJson.json";
    std::string jsonStr = loadFileToString(filePath);

    StaticJsonDocument<4096> doc;
    DeserializationError err = deserializeJson(doc, jsonStr);

    if (err) {
        std::cerr << "JSON parse error (stations): " << err.c_str() << '\n';
        return {};
    }

    vector<StationObject> result;

    JsonArray stations = doc["station"];

    for (JsonObject obj : stations) {
        const char* key = obj["key"] | "";
        const char* name = obj["name"] | "";
        int lon = obj["longitude"] | 0;
        int lat = obj["latitude"] | 0;
        result.emplace_back(key, name, lon, lat);

    }
    
    return result;
}


StationObject APIhandler::getStationFromArray(const vector<StationObject>& array, const string& stationName) 
{
    for (const auto& st : array) {  
        if (st.getName() == stationName) {
            return st;
        }
    }
    throw std::runtime_error("Station not found: " + stationName);
}

vector<HistoricalObject> APIhandler::getHistoricalData(const string& key, int parameter)
{
   



    

    return vector<HistoricalObject>();
}

std::vector<ForecastObject> APIhandler::getForecastNext7Days(const StationObject& stationObject)
{
    std::vector<ForecastObject> result;

    std::string fileToRead = "forecastJson.json";
    std::string jsonStr = loadFileToString(fileToRead);

    DynamicJsonDocument doc(256 * 1024);
    if (deserializeJson(doc, jsonStr)) return result;

    JsonArray series = doc["timeSeries"].as<JsonArray>();
    if (series.isNull()) return result;
    
    for (JsonObject entry : series) {
        const char* timeStr = entry["time"];
        if (!timeStr || !strstr(timeStr, "12:00:00Z")) continue;
        JsonObject data = entry["data"];
        ForecastObject fo{};
        fo.air_pressure_at_mean_sea_level = data["air_pressure_at_mean_sea_level"] | 0;
        fo.air_temperature = data["air_temperature"] | 0.0f;
        fo.cloud_area_fraction = data["cloud_area_fraction"] | 0;
        fo.cloud_base_altitude = data["cloud_base_altitude"] | 0;
        fo.cloud_top_altitude = data["cloud_top_altitude"] | 0;
        fo.high_type_cloud_area_fraction = data["high_type_cloud_area_fraction"] | 0;
        fo.low_type_cloud_area_fraction = data["low_type_cloud_area_fraction"] | 0;
        fo.medium_type_cloud_area_fraction = data["medium_type_cloud_area_fraction"] | 0;
        fo.precipitation_amount_max = data["precipitation_amount_max"] | 0.0f;
        fo.precipitation_amount_mean = data["precipitation_amount_mean"] | 0.0f;
        fo.precipitation_amount_median = data["precipitation_amount_median"] | 0.0f;
        fo.precipitation_amount_min = data["precipitation_amount_min"] | 0.0f;
        fo.precipitation_frozen_part = data["precipitation_frozen_part"] | 0;
        fo.predominant_precipitation_type_at_surface = data["predominant_precipitation_type_at_surface"] | 0;
        fo.probability_of_frozen_precipitation = data["probability_of_frozen_precipitation"] | 0;
        fo.probability_of_precipitation = data["probability_of_precipitation"] | 0;
        fo.relative_humidity = data["relative_humidity"] | 0;
        fo.symbol_code = data["symbol_code"] | 0;
        fo.thunderstorm_probability = data["thunderstorm_probability"] | 0;
        fo.visibility_in_air = data["visibility_in_air"] | 0;
        fo.wind_from_direction = data["wind_from_direction"] | 0;
        fo.wind_speed = data["wind_speed"] | 0.0f;
        fo.wind_speed_of_gust = data["wind_speed_of_gust"] | 0.0f;
        result.emplace_back(fo);
        if (result.size() >= 7) break;
    }
    return result;
}


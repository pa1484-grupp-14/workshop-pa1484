
#include "ApiHandling.h"
#include "StationObject.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"

#include <ArduinoJson.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

static std::string loadFileToString(const std::string& filePath)
{
    std::ifstream inputFile(filePath, std::ios::in | std::ios::binary);
    if (!inputFile) {throw std::runtime_error("Could not open JSON-file: " + filePath);}

    std::ostringstream stringStream;
    stringStream << inputFile.rdbuf();

    return stringStream.str();
}

std::vector<StationObject> APIhandler::getStationsArray(int parameter)
{
    const std::string jsonFile = "./apiLogic/demoInCppMockData/JsonFiles/parameterJson.json";
    std::string jsonContent = loadFileToString(jsonFile);

    JsonDocument document = JsonDocument();
    DeserializationError error = deserializeJson(document, jsonContent);
    if (error) {return {};}

    std::vector<StationObject> stationsResult;

    JsonArray stationsArray = document["station"];

    for (JsonObject stationObj : stationsArray) {
        const char* key = stationObj["key"] | "";
        const char* name = stationObj["name"] | "";
        int longitude = stationObj["longitude"] | 0;
        int latitude = stationObj["latitude"] | 0;
        stationsResult.emplace_back(key, name, longitude, latitude);
    }

    return stationsResult;
}


StationObject APIhandler::getStationFromArray(const std::vector<StationObject>& stations, const std::string& stationName)
{
    for (const auto& station : stations) {

        if (station.getName() == stationName) {return station;}
    }

    throw std::runtime_error("Station not found: " + stationName);
}

vector<HistoricalObject> APIhandler::getHistoricalData(const string& key, int parameter)
{
   



    

    return vector<HistoricalObject>();
}

std::vector<ForecastObject> APIhandler::getForecastNext7Days(const StationObject& station)
{
    std::vector<ForecastObject> forecastResult;

    const std::string jsonFile = "forecastJson.json";
    std::string jsonContent = loadFileToString(jsonFile);

    JsonDocument document = JsonDocument();
    if (deserializeJson(document, jsonContent)) {return forecastResult;}

    JsonArray seriesArray = document["timeSeries"].as<JsonArray>();
    if (seriesArray.isNull()) {return forecastResult;}

    for (JsonObject entry : seriesArray) {
        const char* timeString = entry["time"];
        if (!timeString || !strstr(timeString, "12:00:00Z")) {continue;}

        JsonObject data = entry["data"];
        ForecastObject fo{};
        fo.time = entry["time"] | "";
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
        forecastResult.emplace_back(fo);
        if (forecastResult.size() >= 7) {break;}
    }

    return forecastResult;
}


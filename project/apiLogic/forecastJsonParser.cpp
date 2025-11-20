#include "forecastJsonParser.h" 
#include "StationObject.h"
#include <JsonListener.h>
#include <string>



void ForecastListener::whitespace(char c) { 
    Serial.println("whitespace");
}

void ForecastListener::startDocument() {   
    Serial.println("start document");
}

void ForecastListener::key(String key) {
    Serial.println("key: " + key);
    this->currentKey = key;
    if(key == "time")
        this->isTime = true;
    else if(key == "timeSeries")
        this->isTimeSeries = true;
    else if(key == "data" && !this->enteredData)
        this->enteredData = true;
    
}

void ForecastListener::value(String value) {
    Serial.println("value: " + value);
    if(this->isTime)
    {
        const char* timeValue = value.c_str();
        if(strstr(timeValue, "12:00:00Z"))
            this->isTwelveOClock = true;
        this->isTime = false;
    }
    Serial.println("my Checker: " + String(this->isTwelveOClock) + " : " + String(this->currentKey));
    if(this->isTwelveOClock && this->isTimeSeries)
    {
        if (this->currentKey == "air_pressure_at_mean_sea_level")
            this->forecastObjectToAdd.air_pressure_at_mean_sea_level = value.toInt();

        else if (this->currentKey == "air_temperature")
            this->forecastObjectToAdd.air_temperature = value.toFloat();

        else if (this->currentKey == "cloud_area_fraction")
            this->forecastObjectToAdd.cloud_area_fraction = value.toInt();

        else if (this->currentKey == "cloud_base_altitude")
            this->forecastObjectToAdd.cloud_base_altitude = value.toInt();

        else if (this->currentKey == "cloud_top_altitude")
            this->forecastObjectToAdd.cloud_top_altitude = value.toInt();

        else if (this->currentKey == "high_type_cloud_area_fraction")
            this->forecastObjectToAdd.high_type_cloud_area_fraction = value.toInt();

        else if (this->currentKey == "low_type_cloud_area_fraction")
            this->forecastObjectToAdd.low_type_cloud_area_fraction = value.toInt();

        else if (this->currentKey == "medium_type_cloud_area_fraction")
            this->forecastObjectToAdd.medium_type_cloud_area_fraction = value.toInt();

        else if (this->currentKey == "precipitation_amount_max")
            this->forecastObjectToAdd.precipitation_amount_max = value.toFloat();

        else if (this->currentKey == "precipitation_amount_mean")
            this->forecastObjectToAdd.precipitation_amount_mean = value.toFloat();

        else if (this->currentKey == "precipitation_amount_median")
            this->forecastObjectToAdd.precipitation_amount_median = value.toFloat();

        else if (this->currentKey == "precipitation_amount_min")
            this->forecastObjectToAdd.precipitation_amount_min = value.toFloat();

        else if (this->currentKey == "precipitation_frozen_part")
            this->forecastObjectToAdd.precipitation_frozen_part = value.toInt();

        else if (this->currentKey == "predominant_precipitation_type_at_surface")
            this->forecastObjectToAdd.predominant_precipitation_type_at_surface = value.toInt();

        else if (this->currentKey == "probability_of_frozen_precipitation")
            this->forecastObjectToAdd.probability_of_frozen_precipitation = value.toInt();

        else if (this->currentKey == "probability_of_precipitation")
            this->forecastObjectToAdd.probability_of_precipitation = value.toInt();

        else if (this->currentKey == "relative_humidity")
            this->forecastObjectToAdd.relative_humidity = value.toInt();

        else if (this->currentKey == "symbol_code")
            this->forecastObjectToAdd.symbol_code = value.toInt();

        else if (this->currentKey == "thunderstorm_probability")
            this->forecastObjectToAdd.thunderstorm_probability = value.toInt();

        else if (this->currentKey == "visibility_in_air")
            this->forecastObjectToAdd.visibility_in_air = value.toInt();

        else if (this->currentKey == "wind_from_direction")
            this->forecastObjectToAdd.wind_from_direction = value.toInt();

        else if (this->currentKey == "wind_speed")
            this->forecastObjectToAdd.wind_speed = value.toFloat();

        else if (this->currentKey == "wind_speed_of_gust")
            this->forecastObjectToAdd.wind_speed_of_gust = value.toFloat();
    }
}

void ForecastListener::endArray() {
    Serial.println("end array. ");
}

void ForecastListener::endObject() {
    Serial.println("end object. ");
    if(this->isTwelveOClock && this->isTimeSeries){
        this->forecasts.push_back(this->forecastObjectToAdd);
        this->enteredObject = false;
        this->enteredData = false;
        this->isTwelveOClock = false;
        this->isTimeSeries = false;
        this->itemCount++;
    }
        
}

void ForecastListener::endDocument() {
    Serial.println("end document. ");
}

void ForecastListener::startArray() {
    Serial.println("start array. ");
}

void ForecastListener::startObject() {
    Serial.println("start object. ");
    if(this->isTimeSeries)
        this->enteredObject = true;
}
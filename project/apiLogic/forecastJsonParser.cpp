#include "forecastJsonParser.h" 
#include "StationObject.h"
//#include <JsonListener.h>
#include <string>

/*
void ForecastListener::startDocument() {   
    Serial.println("start document");
}
void ForecastListener::endDocument() {
    Serial.println("end document. ");
}
void ForecastListener::startArray() {}
void ForecastListener::endArray() {}
void ForecastListener::startObject() {
    
    if(state == ListeningState::InTimeSeries)
        state = ListeningState::FilteringObject;
}
void ForecastListener::endObject() {
    
    if(state == ListeningState::ProcessingItem){
        
        forecasts.push_back(forecastObjectToAdd);
        itemCount++;
        state = ListeningState::InTimeSeries;
    } else {
        
    }
        
}
void ForecastListener::whitespace(char c) {}
void ForecastListener::key(String key) {
    this->currentKey = key;
    if(key == "time")
        state = ListeningState::FilteringObject;
    else if(key == "timeSeries")
        state = ListeningState::InTimeSeries;
    
}

void ForecastListener::value(String value) {
    if(state == ListeningState::FilteringObject)
    {
        const char* timeValue = value.c_str();
        if(strstr(timeValue, "12:00:00Z")) {
            state = ListeningState::ProcessingItem;
            this->forecastObjectToAdd.time = value.c_str();
        } else {
            state = ListeningState::InTimeSeries;
        }
            
    }
    else if(state == ListeningState::ProcessingItem)
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

*/

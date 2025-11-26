#include "parameterJsonParser.h"
#include "StationObject.h"
#include <JsonListener.h>
#include <string>



void StationFilterParser::whitespace(char c) {

}

void StationFilterParser::startDocument() {
    state = StationFilter::OutsideStations;
}

void StationFilterParser::key(String key) {
    switch(state) {
        case StationFilter::OutsideStations:
            if(key == "station") state = StationFilter::InsideStation;
            break;
        case StationFilter::InsideStation:
            break;
        case StationFilter::InsideObject:
            if(key == "key")
                state = StationFilter::GettingKey;
            else if(key == "name")
                state = StationFilter::GettingName;
            
                break;
        default:

            break;
    }
}

void StationFilterParser::value(String value) {
    switch(state) {
        case StationFilter::OutsideStations:
            break;
        case StationFilter::InsideStation:
            break;
        case StationFilter::InsideObject:
            break;
        case StationFilter::GettingKey:
            current_station_key = value.toInt();
            state = StationFilter::InsideObject;
            break;
        case StationFilter::GettingName:
            std::string converted_string = std::string(value.c_str());
            int a = converted_string.find("-");
            if(a < 0) {
                current_station_name = converted_string;
            } else {
                current_station_name = converted_string.substr(0,a);
            }
            state = StationFilter::InsideObject;
            break;
    }
}
void StationFilterParser::endArray(){
    
}
void StationFilterParser::endObject() {
    if(state == StationFilter::InsideStation) {
        state = StationFilter::OutsideStations;
    } else if (state == StationFilter::InsideObject) {
        state = StationFilter::InsideStation;
    }
}
void StationFilterParser::endDocument() {
    
}
void StationFilterParser::startArray() {
    
}
void StationFilterParser::startObject() {
    if(state == StationFilter::InsideStation) 
        state = StationFilter::InsideObject;
}

void ExampleListener::whitespace(char c) {
    Serial.println("whitespace");
}

void ExampleListener::startDocument() {
    Serial.println("start document");
}

void ExampleListener::key(String key) {
    Serial.println("key: " + key);
    if(key == "key" && this->stationArrayEntered)
        this->isKey = true;
    else if (key == "name" && this->stationArrayEntered)
        this->isName = true;
    else if (key == "latitude")
        this->isLat = true;
    else if (key == "longitude")
        this->isLon = true;
    else if (key == "station")
        this->stationArrayEntered = true;

}

void ExampleListener::value(String value) {
    Serial.println("value: " + value);
    if (isKey) {
        this->isKey = false;
        this->stationToAdd.setKey(value.toInt());
    } else if (isName) {
        this->stationToAdd.setName(value.c_str());
        this->isName = false;
    } else if (isLat) {
        this->stationToAdd.setLat(value.toFloat());
        this->isLat = false;
    } else if (isLon) {
        this->stationToAdd.setLon(value.toFloat());
        this->isLon = false;
    }

}

void ExampleListener::endArray() {
    Serial.println("end array. ");
}

void ExampleListener::endObject() {
    Serial.println("end object. ");
    if(this->stationArrayEntered)
    {
        this->stations.push_back(this->stationToAdd);
        this->itemCount++;
        this->stationObjectEntered = false;
    }
}

void ExampleListener::endDocument() {
    Serial.println("end document. ");
}

void ExampleListener::startArray() {
    Serial.println("start array. ");
}

void ExampleListener::startObject() {
    Serial.println("start object. ");
    if(this->stationArrayEntered)
        this->stationObjectEntered = true;
}
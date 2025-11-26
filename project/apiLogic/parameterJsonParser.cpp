#include "parameterJsonParser.h"
#include "StationObject.h"
#include <JsonListener.h>
#include <string>



void StationFilterParser::whitespace(char c) {

}

void StationFilterParser::startDocument() {
    Serial.println("Searching stations...");
    state = StationFilter::OutsideStations;
}

void StationFilterParser::key(String key) {
    switch(state) {
        case StationFilter::OutsideStations:
            
            if(key == "station") {
                Serial.println("Entering Stations collection stage 1.");
                state = StationFilter::EnteringStation;
            }
            break;
        case StationFilter::InsideStation:
            break;
        case StationFilter::InsideObject:
            
            Serial.println(key.c_str());
            if(key == "key")
                state = StationFilter::GettingKey;
            else if(key == "name")
                state = StationFilter::GettingName;
            else
                state = StationFilter::GettingIrrelevant;
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
        case StationFilter::GettingIrrelevant:
            state = StationFilter::InsideObject;
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
    if(state == StationFilter::InsideStation) {
        state = StationFilter::OutsideStations;
    } else if (state == StationFilter::GettingIrrelevantArray) {
        Serial.println("exit irrelevant array");
        state = StationFilter::InsideObject;
    }
}
void StationFilterParser::endObject() {
    if (state == StationFilter::InsideObject) {
        if(current_station_key != 0) {
            stations.emplace(current_station_name, current_station_key);
            current_station_key = 0;
            Serial.println(current_station_name.c_str());
        }
        state = StationFilter::InsideStation;
        Serial.println("Exiting Object.");
    } else if (state == StationFilter::GettingIrrelevantObject) {
        Serial.println("exit irrelevant object");
        state = StationFilter::InsideObject;
    }
}
void StationFilterParser::endDocument() {
    Serial.println("Station Search Completed.");
}
void StationFilterParser::startArray() {
    if(state == StationFilter::EnteringStation){
        Serial.println("Entering Station Collection.");
        state = StationFilter::InsideStation;
    } else if (state == StationFilter::GettingIrrelevant) {
        Serial.println("starting irrelevant array");
        state = StationFilter::GettingIrrelevantArray;
    }
}
void StationFilterParser::startObject() {
    if(state == StationFilter::InsideStation) {
        Serial.println("Entering Object.");
        state = StationFilter::InsideObject;
    } else if (state == StationFilter::GettingIrrelevant) {
        Serial.println("starting irrelevant object");
        state = StationFilter::GettingIrrelevantObject;
    }
        
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
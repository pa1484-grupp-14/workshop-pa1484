#include "parameterJsonParser.h"
#include "StationObject.h"
//#include <JsonListener.h>
#include <string>

/*

void StationParser::whitespace(char c) {

}

void StationParser::startDocument() {
    Serial.println("Searching stations...");
    state = StationFilter::OutsideStations;
}

void StationParser::key(String key) {
    switch(state) {
        case StationFilter::OutsideStations:
            
            if(key == "station") {
                state = StationFilter::EnteringStation;
            }
            break;
        case StationFilter::InsideStation:
            break;
        case StationFilter::InsideObject:
            if(key == "key")
                state = StationFilter::GettingKey;
            else if(key == "name")
                state = StationFilter::GettingName;
            else if(key == "latitude")
                state = StationFilter::GettingLatitude;
            else if(key == "longitude")
                state = StationFilter::GettingLongitude;
            else
                state = StationFilter::GettingIrrelevant;
                break;
        default:

            break;
    }
}
StationParser::StationParser(): state(StationFilter::OutsideStations), current_city_name(""), current_station_obj({0,"",0,0}) {}
void StationParser::value(String value) {
    switch(state) {
        case StationFilter::GettingKey:
            current_station_obj.setKey(value.toInt());
            break;
        case StationFilter::GettingLatitude:
            current_station_obj.setLat(value.toFloat());
            break;
        case StationFilter::GettingLongitude:
            current_station_obj.setLon(value.toFloat());
            break;
        case StationFilter::GettingName:
            {
                std::string converted_string = std::string(value.c_str());
                current_station_obj.setName(converted_string);
                int a = converted_string.find("-");
                int b = converted_string.find(" ");
                if(a < 0 && b < 0) {
                    current_city_name = converted_string;
                } else if (b < 0) {
                    current_city_name = converted_string.substr(0,a);
                } else if (a < 0) {
                    current_city_name = converted_string.substr(0,b);
                } else {
                    current_city_name = converted_string.substr(0,min(a,b));
                }
            }
            break;
        case StationFilter::GettingIrrelevant:
            break;
        default:
            return;
    }
    state = StationFilter::InsideObject;
}
void StationParser::startArray() {
    if(state == StationFilter::EnteringStation){
        state = StationFilter::InsideStation;
    } else if (state == StationFilter::GettingIrrelevant) {
        state = StationFilter::GettingIrrelevantArray;
    }
}
void StationParser::startObject() {
    if(state == StationFilter::InsideStation) {
        state = StationFilter::InsideObject;
    } else if (state == StationFilter::GettingIrrelevant) {
        state = StationFilter::GettingIrrelevantObject;
    }
        
}
void StationParser::endArray(){
    if(state == StationFilter::InsideStation) {
        state = StationFilter::OutsideStations;
    } else if (state == StationFilter::GettingIrrelevantArray) {
        state = StationFilter::InsideObject;
    }
}
void StationParser::endObject() {
    if (state == StationFilter::InsideObject) {
        if(current_city_name.length() > 0) {
            stations.emplace(current_city_name, current_station_obj);
            current_city_name = "";
        }
        state = StationFilter::InsideStation;
    } else if (state == StationFilter::GettingIrrelevantObject) {
        state = StationFilter::InsideObject;
    }
}
void StationParser::endDocument() {
    Serial.println("Station Search Completed.");
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
        */
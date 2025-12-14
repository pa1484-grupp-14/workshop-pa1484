#include "parameterJsonParser.h"
#include "StationObject.h"
//#include <JsonListener.h>
#include <string>
#include <iostream>

StationParser::StationParser(): state(StationParserStatus::OutsideStations), current_city_name(""), current_station_obj({0,"",0,0}) {}

void StationParser::whitespace(char c) {}

void StationParser::startDocument() {
    std::cout << "[StationParser] Searching stations..." << std::endl;
    state = StationParserStatus::OutsideStations;
}

void StationParser::key(String key) {
    switch(state) {
        case StationParserStatus::OutsideStations:
            
            if(key == "station") {
                state = StationParserStatus::EnteringStation;
            }
            break;
        case StationParserStatus::InsideStation:
            break;
        case StationParserStatus::InsideObject:
            if(key == "key")
                state = StationParserStatus::GettingKey;
            else if(key == "name")
                state = StationParserStatus::GettingName;
            else if(key == "latitude")
                state = StationParserStatus::GettingLatitude;
            else if(key == "longitude")
                state = StationParserStatus::GettingLongitude;
            else
                state = StationParserStatus::GettingIrrelevant;
                break;
        default:

            break;
    }
}

void StationParser::value(String value) {
    switch(state) {
        case StationParserStatus::GettingKey:
            current_station_obj.setKey(value.toInt());
            break;
        case StationParserStatus::GettingLatitude:
            current_station_obj.setLat(value.toFloat());
            break;
        case StationParserStatus::GettingLongitude:
            current_station_obj.setLon(value.toFloat());
            break;
        case StationParserStatus::GettingName:
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
        case StationParserStatus::GettingIrrelevant:
            break;
        default:
            return;
    }
    state = StationParserStatus::InsideObject;
}

void StationParser::startArray() {
    if(state == StationParserStatus::EnteringStation){
        state = StationParserStatus::InsideStation;
    } else if (state == StationParserStatus::GettingIrrelevant) {
        state = StationParserStatus::GettingIrrelevantArray;
    }
}

void StationParser::startObject() {
    if(state == StationParserStatus::InsideStation) {
        state = StationParserStatus::InsideObject;
    } else if (state == StationParserStatus::GettingIrrelevant) {
        state = StationParserStatus::GettingIrrelevantObject;
    }
        
}

void StationParser::endArray(){
    if(state == StationParserStatus::InsideStation) {
        state = StationParserStatus::OutsideStations;
    } else if (state == StationParserStatus::GettingIrrelevantArray) {
        state = StationParserStatus::InsideObject;
    }
}

void StationParser::endObject() {
    if (state == StationParserStatus::InsideObject) {
        if(current_city_name.length() > 0) {
            std::cout << current_city_name << " " << current_station_obj.getKey() << " " << current_station_obj.getLat() << " " << current_station_obj.getLon() << std::endl;
            stations.emplace(current_city_name, current_station_obj);
            current_city_name = "";
        }
        state = StationParserStatus::InsideStation;
    } else if (state == StationParserStatus::GettingIrrelevantObject) {
        state = StationParserStatus::InsideObject;
    }
}

void StationParser::endDocument() {
    std::cout << "[StationParser] Station Search Completed." << std::endl;
}
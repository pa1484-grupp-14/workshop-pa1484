#include "parameterJsonParser.h"
#include "StationObject.h"
#include <JsonListener.h>
#include <string>



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
        this->stationToAdd.setKey(value.c_str());
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
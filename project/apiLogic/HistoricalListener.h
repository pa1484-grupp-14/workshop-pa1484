#pragma once
#ifdef LILYGO_BUILD
#include <JsonListener.h>
#endif
#ifdef NATIVE_BUILD
#include "nativeReplacements/JsonListener.h"
#endif
#include <vector>
#include <string>
#include <ctime>
#include "HistoricalObject.h"
#include <iostream>

using namespace std;

/* 
This class listens to the JSON streaming parser
It recieves pieces of JSON and turns them into HistoricalObject instances.
*/
class HistoricalListener : public JsonListener {
private:
    vector<HistoricalObject> results;
    bool isVersion2 = false;
    string currentKey = "";
    long long tempTimestamp = 0;
    float tempValue = 0.0f;
    string tempRefDate = "";
    
public:
    HistoricalListener() {}

    void key(String key) override {
        currentKey = key.c_str();
    }

    void value(String value) override {
        if (currentKey == "from") {
            //isVersion2 = true;
        }

        if (currentKey == "date") {
            tempTimestamp = std::stoll(value.c_str());
        }

        if (currentKey == "ref") {
            tempRefDate = value.c_str();
        }

        if (currentKey == "value") {
            tempValue = value.toFloat();
        }
    }


    void endObject() override {
        
        if (!isVersion2 && tempTimestamp != 0) {
            results.push_back(HistoricalObject(tempTimestamp / 1000, tempValue));
        }

        tempTimestamp = 0;
        tempValue = 0.0f;
        tempRefDate = "";
    }

    void startDocument() override {
        std::cout << "[HistoricalListener] Finishing parse of historical data points." << std::endl;
    }

    void endDocument() override {
        std::cout << "[HistoricalListener] Starting parse of historical data points." << std::endl;
    }

    void startObject() override {}
    void startArray() override {}
    void endArray() override {}
    void whitespace(char c) override {}

    vector<HistoricalObject>& getResults() {
        return results;
    }
    
    bool isVersion2Data() const {
        return isVersion2;
    }
};
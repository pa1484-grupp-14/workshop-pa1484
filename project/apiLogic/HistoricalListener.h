
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
        std::cout << "[HistoricalListener] Finished object: " << tempTimestamp << "," << tempValue << "," << tempRefDate << "," << isVersion2 << std::endl;
        if (isVersion2 && tempRefDate != "") {
            std::cout << "[HistoricalListener] Pushing new historical object. (Version 2)" << std::endl;
            results.push_back(HistoricalObject(tempRefDate, tempValue));
        }

        if (!isVersion2 && tempTimestamp != 0) {
            std::time_t seconds = tempTimestamp / 1000;
            char buffer[20];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&seconds));
            std::cout << "[HistoricalListener] Pushing new historical object. (Version 1)" << std::endl;
            results.push_back(HistoricalObject(string(buffer), tempValue));
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

    vector<HistoricalObject> getResults() {
        return results;
    }

    bool isVersion2Data() const {
        return isVersion2;
    }
};
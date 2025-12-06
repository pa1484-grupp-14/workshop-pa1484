#include <JsonListener.h>
#include <vector>
#include <string>
#include <ctime>
#include "HistoricalObject.h"

using namespace std;

class HistoricalListener : public JsonListener {
    private:
        vector<HistoricalObject results;
        bool isVersion2 = false;
        string currentKey = "";
        long tempTimestamp = 0;
        float tempValue = 0.0f;
        string tempRefDate = "";
    
    public:
        HistoricalListener() {}

        void key(string key) override {
            currentKey = key;
        }

        void value(string value) override {
            if (currentKey == "from") {
                isVersion2 = true;
            }

            if (currentKey == "date") {
                tempTimestamp = stol(value);
            }

            if (currentKey == "ref") {
                tempRefDate = value;
            }

            if (currentKey == "value") {
                tempValue = stof(value);
            }
        }

        void endObject() override {
            if (isVersion2 && tempRefDate != "") {
                results.push_back(HistoricalObject(tempRefDate, tempValue));
            }

            if (!isVersion2 && tempTimestamp != 0) {
                time_t seconds = tempTimestamp / 1000;
                char buffer[20];
                strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&seconds));

                results.push_back(HistoricalObject(string(buffer), tempValue));
            }

            tempTimestamp = 0;
            tempValue = 0.0f;
            tempRefDate = "";
        }

        void startDocument() override {}
        void endDocument() override {}
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
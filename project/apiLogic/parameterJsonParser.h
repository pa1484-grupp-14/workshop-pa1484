#pragma once
#include "apiLogic/StationObject.h"

#ifdef LILYGO_BUILD
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#else
#include "nativeReplacements/JsonListener.h"
#include "nativeReplacements/JsonStreamingParser.h"
#include "nativeReplacements/String.h"
#endif

#include <vector>
#include <unordered_map>
#include <string>

enum StationParserStatus {
  OutsideStations,
  EnteringStation,
  InsideStation,
  InsideObject,
  GettingKey,
  GettingName,
  GettingLatitude,
  GettingLongitude,
  GettingIrrelevant,
  GettingIrrelevantArray,
  GettingIrrelevantObject,
};

// This class used to be used to fetch weather stations, 
// However since they are now fixed
class StationParser: public JsonListener {
    private:
    char filter;
    StationParserStatus state;
    std::string current_city_name;
    StationObject current_station_obj;

    public: 
    StationParser();
    std::unordered_map<std::string, StationObject> stations;

    void whitespace(char c) override;
  
    void startDocument() override;

    void key(String key) override;

    void value(String value) override;

    void endArray() override;

    void endObject() override;

    void endDocument() override;

    void startArray() override;

    void startObject() override;
};
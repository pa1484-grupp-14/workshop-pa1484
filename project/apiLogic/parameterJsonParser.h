#pragma once

#include "StationObject.h"
#include "JsonListener.h"
#include <vector>
#include <unordered_map>
#include <string>


enum StationFilter {
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

class StationParser: public JsonListener {
    private:
    char filter;
    StationFilter state;
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


class ExampleListener: public JsonListener {  
  private: 
    bool isKey = false;
    bool isName = false; 
    bool isLon = false;
    bool isLat = false;
    bool stationArrayEntered = false;
    bool stationObjectEntered = false; 
    StationObject stationToAdd{1, "", 1, 1};

  public:  
    int itemCount = 0;
    vector<StationObject> stations;   
    
    virtual void whitespace(char c);
  
    virtual void startDocument();

    virtual void key(String key);

    virtual void value(String value);

    virtual void endArray();

    virtual void endObject();

    virtual void endDocument();

    virtual void startArray();

    virtual void startObject();
};

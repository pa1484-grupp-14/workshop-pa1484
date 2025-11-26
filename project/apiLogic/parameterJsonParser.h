#pragma once

#include "StationObject.h"
#include "JsonListener.h"
#include <vector>
#include <unordered_map>
#include <string>


enum StationFilter {
  OutsideStations = 0,
  EnteringStation = 1,
  InsideStation = 2,
  InsideObject = 3,
  GettingKey = 4,
  GettingName = 5,
  GettingIrrelevant = 6,
  GettingIrrelevantArray = 7,
  GettingIrrelevantObject = 8,
};

class StationFilterParser: public JsonListener {
    private:
    char filter;
    StationFilter state;
    std::string current_station_name;
    int current_station_key;

    public: 
    std::unordered_map<std::string, int> stations;

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

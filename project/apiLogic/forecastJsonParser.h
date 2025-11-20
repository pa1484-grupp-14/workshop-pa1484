#pragma once

#include "ForecastObject.h"
#include "JsonListener.h"
#include <vector>

class ForecastListener: public JsonListener {  
  private: 
    bool isTimeSeries;
    bool isTwelveOClock;
    bool isTime;
    bool enteredData;
    bool enteredObject;
    ForecastObject forecastObjectToAdd;
    String currentKey; 

  public:  
    std::vector<ForecastObject> forecasts;
    int itemCount;  
    
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

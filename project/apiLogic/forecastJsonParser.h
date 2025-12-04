#pragma once

#include "ForecastObject.h"
#ifdef LILYGO_BUILD
#include "JsonListener.h"
#else
#include "nativeReplacements/JsonListener.h"
#endif
#include <vector>


enum ListeningState {
  Pending = 0,
  InTimeSeries,
  StartingTimeSeries,
  ProcessingItem,
  FilteringObject,

};

class ForecastListener: public JsonListener {  
  private: 
    ListeningState state;
    ForecastObject forecastObjectToAdd;
    String currentKey; 

  public:  
    int itemCount;
    std::vector<ForecastObject> forecasts;
    
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

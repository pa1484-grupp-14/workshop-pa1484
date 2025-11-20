#pragma once

#include "StationObject.h"
#include "JsonListener.h"
#include <vector>

class ExampleListener: public JsonListener {  
  private: 
    bool isKey = false;
    bool isName = false; 
    bool isLon = false;
    bool isLat = false;
    bool stationArrayEntered = false;
    bool stationObjectEntered = false; 
    StationObject stationToAdd{"", "", 1, 1};

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

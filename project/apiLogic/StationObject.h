#pragma once
#include <String> 
#include <memory>
#include "Arduino.h"  

class StationObject
{
private:
    String key;
    String name; 
    int longitude;
    int latitude;
public: 
    StationObject(String key, String name, int longitude, int latitude);
    String getKey();
    String getName();
    int getLon(); 
    int getLat();
    
    void setKey(String key);
    void setName(String name);
    void setLon(int lon); 
    void setLat(int lat);
};

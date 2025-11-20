#pragma once
#include <string>

using namespace std;
class StationObject
{
private:
    string key;
    string name;
    float longitude;
    float latitude;
public:
    StationObject(string key, string name, float longitude, float latitude);
    string getKey() const;
    string getName() const;
    float getLon() const;
    float getLat() const;

    void setKey(string key);
    void setName(string name);
    void setLon(float lon);
    void setLat(float lat);
};

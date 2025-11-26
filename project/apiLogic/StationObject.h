#pragma once
#include <string>

using namespace std;
class StationObject
{
private:
    int key;
    string name;
    float longitude;
    float latitude;
public:
    StationObject(int key, string name, float longitude, float latitude);
    int getKey() const;
    string getName() const;
    float getLon() const;
    float getLat() const;

    void setKey(int key);
    void setName(string name);
    void setLon(float lon);
    void setLat(float lat);
};

#pragma once
#include <string>

using namespace std;
class StationObject
{
private:
    string key;
    string name;
    int longitude;
    int latitude;
public:
    StationObject(const string& key, const string& name, int longitude, int latitude);
    const string& getKey() const;
    const string& getName() const;
    int getLon();
    int getLat();

    void setKey(const string& key);
    void setName(const string& name);
    void setLon(int lon);
    void setLat(int lat);
};
#include "StationObject.h"

StationObject::StationObject(int key, string name, float longitude, float latitude) : key(key), name(name), longitude(longitude), latitude(latitude) {} 

int StationObject::getKey() const 
{
    return this->key;
}

string StationObject::getName() const 
{
    return this->name;
}

float StationObject::getLon() const
{
    return this->longitude;
}

float StationObject::getLat() const
{
    return this->latitude;
}

void StationObject::setKey(int key) 
{
    this->key = key;
}

void StationObject::setName(string name)
{
    this->name = name;
}

void StationObject::setLon(float lon) 
{
    this->longitude = lon;
}

void StationObject::setLat(float lat)
{
    this->latitude = lat;
}

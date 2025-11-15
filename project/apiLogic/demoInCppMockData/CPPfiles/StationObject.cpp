#include "StationObject.h"

StationObject::StationObject(string key, string name, int longitude, int latitude) : key(key), name(name), longitude(longitude), latitude(latitude) {} 

string StationObject::getKey() 
{
    return this->key;
}

string StationObject::getName() 
{
    return this->name;
}

int StationObject::getLon()
{
    return this->longitude;
}

int StationObject::getLat()
{
    return this->latitude;
}

void StationObject::setKey(string key)
{
    this->key = key;
}

void StationObject::setName(string name)
{
    this->name = name;
}

void StationObject::setLon(int lon)
{
    this->longitude = lon;
}

void StationObject::setLat(int lat)
{
    this->latitude = lat;
}
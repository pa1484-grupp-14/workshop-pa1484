#include "StationObject.h"

StationObject::StationObject(String key, String name, int longitude, int latitude) : key(key), name(name), longitude(longitude), latitude(latitude){}

String StationObject::getKey()
{
    return this->key;
}

String StationObject::getName()
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

void StationObject::setKey(String key)
{
    this->key = key;
}

void StationObject::setName(String name)
{
    this->name = name;
}

void StationObject::setLon(int lon)
{
    this->longitude = lon;
}

void StationObject::setLat(int lat)
{
    this->latitude = latitude;
}

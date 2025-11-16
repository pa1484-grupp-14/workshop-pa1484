#include "StationObject.h"

StationObject::StationObject(const string& key, const string& name, int longitude, int latitude) : key(key), name(name), longitude(longitude), latitude(latitude) {}

const string& StationObject::getKey() const
{
    return this->key;
}

const string& StationObject::getName() const
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

void StationObject::setKey(const string& key)
{
    this->key = key;
}

void StationObject::setName(const string& name)
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
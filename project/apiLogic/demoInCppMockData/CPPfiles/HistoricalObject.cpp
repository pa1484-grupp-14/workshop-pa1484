#include "HistoricalObject.h"


HistoricalObject::HistoricalObject(string date, float value) : date(date), value(value) {}

string HistoricalObject::getDate()
{
    return this->date;
}

float HistoricalObject::getValue()
{
    return this->value;
}

void HistoricalObject::setDate(string date)
{
    this->date = date;
}

void HistoricalObject::setValue(float value) 
{
    this->value = value;
}
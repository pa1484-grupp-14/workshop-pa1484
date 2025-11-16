#include "HistoricalObject.h"


HistoricalObject::HistoricalObject(const string& date, float value) : date(date), value(value) {}

const string& HistoricalObject::getDate() const
{
    return this->date;
}

float HistoricalObject::getValue() const
{
    return this->value;
}

void HistoricalObject::setDate(const string& date)
{
    this->date = date;
}

void HistoricalObject::setValue(float value) 
{
    this->value = value;
}
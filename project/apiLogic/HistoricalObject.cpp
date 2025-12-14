#include "HistoricalObject.h"


HistoricalObject::HistoricalObject(long long date, float value) : date(date), value(value) {}

const long long HistoricalObject::getDate() const {
    return this->date;
}

float HistoricalObject::getValue() const {
    return this->value;
}

void HistoricalObject::setDate(long long date)
{
    this->date = date;
}

void HistoricalObject::setValue(float value) 
{
    this->value = value;
}

#include "HistoricalObject.h"


HistoricalObject::HistoricalObject(string date, float value) : date(date), value(value) {}

const std::string& HistoricalObject::getDate() const {
    return this->date;
}

float HistoricalObject::getValue() const {
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

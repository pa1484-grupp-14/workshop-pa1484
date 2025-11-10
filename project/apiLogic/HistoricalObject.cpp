#include "HistoricalObject.h"

HistoricalObject::HistoricalObject(String date, float value) : date(date), value(value){}

String HistoricalObject::getDate()
{
    return this->date;
}

float HistoricalObject::getValue()
{
    return this->value;
}

void HistoricalObject::setDate(String date)
{
    this->date = date;
}

void HistoricalObject::setValue(float value)
{
    this->value = value;
}

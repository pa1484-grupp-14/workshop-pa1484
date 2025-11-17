#pragma once
#include <string>

using namespace std;
class HistoricalObject
{
private:
	string date;
	float value;
public:
	HistoricalObject(const string& date, float value);
	const string& getDate() const;
	float getValue() const;
	void setDate(const string& date);
	void setValue(float value);
};
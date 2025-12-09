#pragma once
#include <string> 

using namespace std;
class HistoricalObject
{
private:
	string date;
	float value;
public:
	HistoricalObject(string date, float value);   
	const string& getDate() const;
    float getValue() const;
	void setDate(string date);  
	void setValue(float value);
};


#pragma once
#include <string> 

using namespace std;
class HistoricalObject
{
private:
	long long date;
	float value;
public:
	HistoricalObject(long long date, float value);   
	const long long getDate() const;
    float getValue() const;
	void setDate(long long date);  
	void setValue(float value);
};


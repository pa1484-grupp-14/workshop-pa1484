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
	string getDate();   
	float getValue();   
	void setDate(string date);  
	void setValue(float value);
};


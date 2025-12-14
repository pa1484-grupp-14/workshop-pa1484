#pragma once
#include <string> 

using namespace std;
class HistoricalObject
{
	private:
	//Timestamp
	long long date;	
	//Sample
	float value;	

	public:
	//Constructor
	HistoricalObject(long long date, float value);   
	
	//Getters
	const long long getDate() const;
    float getValue() const;
	
	//Setters
	void setDate(long long date);  
	void setValue(float value);
};


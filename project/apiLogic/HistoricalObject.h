#include <String> 
#include <memory>
#include "Arduino.h"  

class HistoricalObject
{
private:
	String date; 
	float value;
public:
	HistoricalObject(String date, float value);
	String getDate();
	float getValue();
	void setDate(String date);
	void setValue(float value);
};
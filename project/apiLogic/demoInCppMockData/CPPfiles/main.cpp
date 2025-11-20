// API-Testing-Classes-NewOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ApiHandling.h"
#include "ForecastObject.h"
#include "HistoricalObject.h"
#include <iostream>
#include <string>
#include <ArduinoJson.h>

using namespace std;

int main()
{
    APIhandler handler;

    vector<StationObject> myStationArr = handler.getStationsArray(1);
    StationObject station = handler.getStationFromArray(myStationArr, "Abisko Aut"); 


    vector<HistoricalObject> histRaw = handler.getHistoricalData(station.getKey(), 1);

    vector<ForecastObject> forecast = handler.getForecastNext7Days(station);

    std::cout << "Station: " << station.getName() << "\n";
    std::cout << "Prognosdagar: " << forecast.size() << "\n";



    std::cout << station.getKey();

    return 0;

}
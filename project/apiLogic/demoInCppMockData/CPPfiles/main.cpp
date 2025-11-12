// API-Testing-Classes-NewOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ApiHandling.h"
#include <iostream>
#include <string>
#include <ArduinoJson.h> 

using namespace std;

int main()
{  
    APIhandler handler;
    vector<StationObject> myArr = handler.getSationsArray(1);
    StationObject obj = handler.getStationFromArray(myArr, "Abisko Aut"); 

    std::cout << obj.getKey();

    return 0;

}
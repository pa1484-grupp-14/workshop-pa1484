

#include "ApiHandling.h"
#include <ArduinoJson.h>
#include <iostream>
#include <string>

vector<StationObject> APIhandler::getSationsArray(int parameter)
{
    vector<StationObject> array;
    DynamicJsonDocument doc(100000000);

    std::ifstream jsonData("C:/Users/asrie/OneDrive/Skrivbord/Misc/Personal/Projects/BTH/ProgramvaruutvecklingLearning/API-Testing/API-Testing-Classes-NewOne/API-Testing-Classes-NewOne/parameterJson.json", ios::binary); 
    if (!jsonData.is_open()) {
        cerr << "Could not open file!" << endl;
    }

    string line, jsonString;
    while (getline(jsonData, line))
        jsonString += line + "\n";
    //cout << jsonString;
 

    DeserializationError error = deserializeJson(doc, jsonString.c_str()); 
    if (error) {
        cout << "Something went wrong when deserializing the document: " << error.c_str() << "\n"; 
    }

    JsonArray objects = doc["station"].as<JsonArray>(); 
    if (objects.isNull()) { 
        cout << "Could not find 'Station' array in JSON.\n"; 
        return vector<StationObject>(); 
    }

    for (JsonObject obj : objects) {
     
        const char* name = obj["name"].as<const char*>();
        const char* key = obj["key"].as<const char*>(); 
        int lon = obj["longitude"].as<int>();
        int lat = obj["latitude"].as<int>();
        StationObject object(key, name, lon, lat);
        array.push_back(object);
    }
    
    return array;
}

StationObject APIhandler::getStationFromArray(vector<StationObject> array, string stationName) 
{
    int count = 0;
    while (count != array.size())
    {
        if (array[count].getName() == stationName)
        {
            return array[count];
        }
        count++;
    }
    throw("Station not found");
}

vector<HistoricalObject> APIhandler::getHistoricalData(string key, int parameter)
{
   



    

    return vector<HistoricalObject>();
}

vector<ForecastObject> APIhandler::getForecastNext7Days(StationObject stationObject)
{

    vector<ForecastObject> array;  
    DynamicJsonDocument doc(100000000);

    std::ifstream jsonData("C:/Users/asrie/OneDrive/Skrivbord/Misc/Personal/Projects/BTH/ProgramvaruutvecklingLearning/API-Testing/API-Testing-Classes-NewOne/API-Testing-Classes-NewOne/forecastJson.json", ios::binary);
    if (!jsonData.is_open()) {
        cerr << "Could not open file!" << endl;
    }

    string line, jsonString;
    while (getline(jsonData, line))
        jsonString += line + "\n";

    DeserializationError error = deserializeJson(doc, jsonString.c_str());
    if (error) {
        cout << "Something went wrong when deserializing the document: " << error.c_str() << "\n";
    }

    JsonArray objects = doc["timeSeries"].as<JsonArray>();

    if (objects.isNull()) { 
        cout << "Could not find 'Station' array in JSON.\n";
        return vector<ForecastObject>(); 
    }

    for (JsonObject obj : objects) 
    {
        
        //array.push_back(obj); 
    }
  


    return vector<ForecastObject>(); 
}


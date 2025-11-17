#include <SPI.h>
#include <HTTPClient.h>
#include <string> 
#include <memory>
#include <unordered_map>
#include <ArduinoJson.h>  
#include "Arduino.h"

using namespace std;
class APIhandler
{
private:
    HTTPClient http; 
    String baseURLHistorical = "https://opendata-download-metobs.smhi.se/api";
    String baseURLForecast = "https://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon";
public:
    String getSationsArray(int parameter);    
    String getStationFromArray(String array, String stationName);
    String getHistoricalData(String key, int parameter);
    String getForecastNext7Days(String StationObject);
};
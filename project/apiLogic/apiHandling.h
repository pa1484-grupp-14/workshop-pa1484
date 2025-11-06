#include <SPI.h>
#include <HTTPClient.h>
#include <String> 
#include <memory>
#include <unordered_map>
#include "Arduino.h"

using namespace std;
class APIhandler
{
private:
    HTTPClient http; 
    String baseUrl = "https://opendata-download-metobs.smhi.se/api";
    String query;  
public:
    String getSationInfo(String stationName, int typeOfData);  
    String getData(String stationName, int typeOfData, String duration, int intervall);
    String getDataLatestMonths(String stationName, int typeOfData);
    void setQuerry(String query);
    void setHttp(String url);
    String getQuerry();
};
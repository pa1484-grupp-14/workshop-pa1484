#include "ApiHandling.h"

#include <ArduinoJson.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "ForecastObject.h"
#include "HistoricalListener.h"
#include "StationObject.h"
#include "forecastJsonParser.h"
#include "parameterJsonParser.h"

std::unordered_map<std::string, std::vector<ForecastObject>>
    APIhandler::cached_forecasts =
        std::unordered_map<std::string, std::vector<ForecastObject>>();
int APIhandler::cached_parameter = 0;
std::unordered_map<std::string, StationObject> APIhandler::cached_stations = {
    {"Karlskrona", StationObject{65090, "Karlskrona", 15.589, 56.15}},
    {"Malmö", StationObject{53300, "Malmö", 13.3787, 55.5231}},
    {"Stockholm", StationObject{97400, "Stockholm", 17.9545, 59.6269}},
    {"Göteborg", StationObject{72420, "Göteborg", 12.2919, 57.6764}},
    {"Kiruna", StationObject{180940, "Kiruna", 20.3387, 67.827}}};

StationObject APIhandler::getStationFromArray(
    const std::unordered_map<std::string, StationObject>& array,
    const std::string& stationName) {
  return array.at(stationName);
}

#include <map>
#ifdef LILYGO_BUILD
#include <HTTPClient.h>
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#endif
#ifdef NATIVE_BUILD
#include "nativeReplacements/HTTPClient.h"
#include "nativeReplacements/JsonListener.h"
#include "nativeReplacements/JsonStreamingParser.h"
#endif

std::vector<HistoricalObject> APIhandler::getHistoricalData(
    const StationObject& station, int parameter) {
  string url =
      "http://opendata-download-metobs.smhi.se/api/version/1.0/parameter/" +
      to_string(parameter) + "/station/" + to_string(station.getKey()) +
      "/period/latest-months/data.json";

  WiFiClient client;
  HTTPClient http;

  http.begin(client, url.c_str());
  int httpCode = http.GET();

  if (httpCode != 200) {
    return vector<HistoricalObject>();
  }

  HistoricalListener listener;
  JsonStreamingParser parser;
  parser.setListener(&listener);

  WiFiClient* stream = http.getStreamPtr();
  while (stream->connected() || stream->available()) {
    char c = stream->read();
    parser.parse(c);
  }

  http.end();

  return listener.getResults();
}

/*
This is a helper function that gets the average per day
*/
std::vector<HistoricalObject> APIhandler::averageByDay(
    const vector<HistoricalObject>& raw) {
  std::map<long long, std::vector<float>> grouped;

  // Group values by their date
  for (const auto& obj : raw) {
    grouped[obj.getDate()].push_back(obj.getValue());
  }

  // Will hold the averaged results
  std::vector<HistoricalObject> averagedResults;

  // Iterates through each date >> list of values
  for (const auto& entry : grouped) {
    const long long& date = entry.first;
    const std::vector<float>& values = entry.second;

    // Computes the sum of values for the date
    float sum = 0;
    for (float v : values) {
      sum += v;
    }

    // Computes the average
    float avg = sum / values.size();

    // ? Push the averaged HistoricalObject into the output vector
    averagedResults.emplace_back(date, avg);
  }
  return averagedResults;
}
void APIhandler::getForecastNext7DaysAsync(
        const StationObject& stationObject,
        void (*success_cb)(std::vector<ForecastObject>&), void (*failure_cb)()) {
    
    //if a request is already in progress, then cancel it
    if (forecastFetch != nullptr) {
        forecastFetch->http.end();
        delete forecastFetch;
        forecastFetch == nullptr;
    }

    //allocate new request
    ForecastRequest* fetch = new ForecastRequest{
        WiFiClient(),       HTTPClient(), JsonStreamingParser(),
        ForecastListener(), success_cb,   failure_cb};
    float lon = stationObject.getLon();
    float lat = stationObject.getLat();

    //generate the URL
    String url =
        "http://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/"
        "geotype/point/lon/";
    url += String(lon) + "/" + "lat/" + String(lat) + "/data.json";
    
    //wait max 1 second for initial response
    fetch->client.setTimeout(1);

    //do the HTTP fetch
    if (fetch->http.begin(fetch->client, url)) {
        int code = fetch->http.GET();
        if (code == HTTP_CODE_OK) {
            //handle success, start processing in the background
            forecastFetch = fetch;
            fetch->parser.setListener(&fetch->listener);
            std::cout << "[APIHandler] Fetching forecast asynchronously!."
                        << std::endl;
        } else {
            //handle failure
            fetch->http.end();
            if (failure_cb) {
                failure_cb();
            }
            delete fetch;
            std::cout << "[APIHandler] Failed to fetch forecast" << std::endl;
        }
    }
}
std::vector<ForecastObject> APIhandler::getForecastNext7Days(
    const StationObject& stationObject) {
  float lon = stationObject.getLon();
  float lat = stationObject.getLat();
  String url =
      "http://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/"
      "geotype/point/lon/";
  url += String(lon) + "/" + "lat/" + String(lat) + "/data.json";

  // Your Domain name with URL path or IP address with path
  WiFiClient client;
  HTTPClient http;
  JsonStreamingParser parser;
  ForecastListener listener;

  // If your need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

  if (http.begin(client, url)) {

    int code = http.GET();
    if (code == HTTP_CODE_OK) {

      // Get stream
      WiFiClient* stream = http.getStreamPtr();

      // Initialize your streaming parser
      parser.setListener(&listener);

      // Read response in chunks
      const int BUFFER_SIZE = 512;
      char buffer[BUFFER_SIZE];

      auto before = millis();
      while ((stream->connected() || stream->available()) &&
             listener.itemCount != 7) {
        int len = stream->readBytes(buffer, BUFFER_SIZE);
        for (int i = 0; i < len; i++) {
          parser.parse((char)buffer[i]);
        }
      }
      auto after = millis();
      std::cout << "[APIHandler] took " << after - before
                << "ms to parse all forecast data." << std::endl;
    } else {
      std::cout << "[APIHandler] Failed to fetch forecast data." << std::endl;
      return vector<ForecastObject>();
    }

    http.end();
  }
  return listener.forecasts;
}

StationRequest* APIhandler::stationFetch = nullptr;
ForecastRequest* APIhandler::forecastFetch = nullptr;
HistoricRequest* APIhandler::historyFetch = nullptr;

void APIhandler::getStationsArrayAsync(
    int parameter,
    void (*success_cb)(std::unordered_map<std::string, StationObject>&),
    void (*failure_cb)()) {
  //previously there was code here to fetch stations,
  //this is now infallible, due to updated requirements.
  success_cb(cached_stations);
}
std::unordered_map<std::string, StationObject> APIhandler::getStationsArray(
    int parameter) {
  //previously there was code here to fetch stations,
  //this is now infallible, due to updated requirements.
  return cached_stations;
}

// Start fetching historic weather data asynchronously
void APIhandler::getHistoricalDataAsync(
    const StationObject& station, int parameter,
    void (*success_cb)(std::vector<HistoricalObject>&), void (*failure_cb)()) {
  
    //If theres already a fetch going on, cancel it.
    if (historyFetch != nullptr) {
        historyFetch->http.end();
        delete historyFetch;
        historyFetch == nullptr;
    }

    //Allocate a new fetch
    HistoricRequest* fetch = new HistoricRequest{
        WiFiClient(),         HTTPClient(), JsonStreamingParser(),
        HistoricalListener(), success_cb,   failure_cb};
    
    //Generate URL
    string url =
        "http://opendata-download-metobs.smhi.se/api/version/1.0/parameter/" +
        to_string(parameter) + "/station/" + to_string(station.getKey()) +
        "/period/latest-months/data.json";

    //Wait max 1 second for initial server response
    fetch->client.setTimeout(1);

    //Do the HTTP request
    if (fetch->http.begin(fetch->client, String(url.c_str()))) {
        if (fetch->http.GET() == HTTP_CODE_OK) {
            //setup the listener so data from the request can be fetched in the background
            fetch->parser.setListener(&fetch->listener);
            historyFetch = fetch;
            std::cout << "[APIHandler] Fetching historical data asynchronously!."
                    << std::endl;
        } else {
            //handle failure of the call
            if (failure_cb != nullptr) (*failure_cb)();
            fetch->http.end();
            delete fetch;
            std::cout << "[APIHandler] Failed to fetch historical data"
                    << std::endl;
        }
  }
}

// do quick background processing, fetching chunks of ongoing requests
void APIhandler::process() {
    const int BUFFER_SIZE = 1024;
    if (forecastFetch != nullptr) {
        //NOTE: return nullptr when connection is closed, so doubled up as connection status
        WiFiClient* stream = forecastFetch->http.getStreamPtr();
        if (stream) {
            //create a chunk
            char buffer[BUFFER_SIZE];
            //fetch and parse it
            auto available = stream->available();
            if (available > 0) {
                int len = stream->readBytes(buffer, min(BUFFER_SIZE, available));
                for (int i = 0; i < len; i++) forecastFetch->parser.parse(buffer[i]);
            }
        } else {
            //assume success when the connection closes
            forecastFetch->http.end();
            forecastFetch->success_cb(forecastFetch->listener.forecasts);
            delete forecastFetch;
            forecastFetch = nullptr;
            std::cout << "[APIHandler] finished async forecast fetch" << std::endl;
        }
    }
    if (historyFetch != nullptr) {
        //NOTE: return nullptr when connection is closed, so doubled up as connection status
        WiFiClient* stream = historyFetch->http.getStreamPtr();
        if (stream) {
            //create a chunk
            char buffer[BUFFER_SIZE];
            //fetch and parse it
            auto available = stream->available();
            if (available > 0) {
                int len = stream->readBytes(buffer, min(BUFFER_SIZE, available));
                for (int i = 0; i < len; i++) historyFetch->parser.parse(buffer[i]);
            }
        } else {
            //assume success when the connection closes
            historyFetch->http.end();
            historyFetch->success_cb(historyFetch->listener.getResults());
            delete historyFetch;
            historyFetch = nullptr;
            std::cout << "[APIHandler] finished async historic fetch" << std::endl;
        }
    }
}

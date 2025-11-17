// (c) Copyright 2010-2012 MCQN Ltd.
// Released under Apache License, version 2.0
//
// Simple example to show how to use the HttpClient library
// Get's the web page given at http://<kHostname><kPath> and
// outputs the content to the serial port

#include "apiHandling.h"
// This example downloads the URL "http://arduino.cc/"


void getData()
{
    HTTPClient http;
    String serverName = "https://opendata-download-metobs.smhi.se/api"; 
    String query = serverName + ".json";
      
      // Your Domain name with URL path or IP address with path
    http.begin(query.c_str());
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Send HTTP GET request
    int httpResponseCode = http.GET();
      
    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}



/*

  this->http.begin("http://opendata-download-metobs.smhi.se/api/version/latest/parameter/"+String(typeOfData)+".json");
    int httpResponseCode = this->http.GET();
    if(httpResponseCode  > 0) 
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode );
        String StringData = http.getString();
        
        http.end();
        return StringData;  
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode );
        http.end();
    }
*/

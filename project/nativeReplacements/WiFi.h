
#pragma once
#define WIFI_STA 0
class Wifi {
    public:
    void mode(int dummy) {};
    void begin(const char* ssid, const char* pass) {};
};
static Wifi WiFi;
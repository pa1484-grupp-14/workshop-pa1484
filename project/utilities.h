#pragma once
#ifdef LILYGO_BUILD
#include <WiFi.h>
#endif

bool is_wifi_connected() {
    #ifdef LILYGO_BUILD
    return WiFi.status() == WL_CONNECTED;
    #else
    return false;
    #endif
}
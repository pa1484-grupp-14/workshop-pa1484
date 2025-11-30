#include <WiFi.h>

bool is_wifi_connected() {
    return WiFi.status() == WL_CONNECTED;
}
#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h"
#include <WiFi.h>

#define SSID "Vodafone-E08636455"
#define PASSWORD_WIFI "Spassocasa2025!"

void initWiFi();
bool isWiFiConnected();

#endif
/**
 * @file Wifi.h
 * @brief This file defines the Wifi functions available.
 */

#ifndef WIFI_H
#define WIFI_H

#include "Arduinio.h"
#include "esp_log.h"

// Credenziali WiFi
#define SSID "Vodafone-E08636455"
#define PASSWORD_WIFI "Spassocasa2025!"

void initWiFi();
bool isWiFiConnected();

#endif // WIFI_H    
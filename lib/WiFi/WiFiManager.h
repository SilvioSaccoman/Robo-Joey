#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h"
#include <WiFi.h>
#include "InputManager.h"
#include <WiFiUdp.h>
#include "config.h"

/**
 * Initialize WiFi connection and start the UDP receiver task
 */
void initWiFi();

/**
 * Check if the device is currently connected to WiFi
 */
bool isWiFiConnected();

/**
 * Task function to receive UDP packets and process them as ControlPacket structures
 */
void udpReceiverTask(void *pvParameters);

#endif
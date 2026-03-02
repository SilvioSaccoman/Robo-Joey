#include "WiFiManager.h"
// Sostituisci con le tue credenziali
const char* ssid_global = SSID;
const char* pass_global = PASSWORD_WIFI;

void initWiFi() {
    ESP_LOGI("WIFI", "Tentativo di connessione a: %s\n", ssid_global);
    
    // Imposta la modalità station ed evita che cerchi di riconnettersi a reti vecchie
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(); 
    delay(100);

    WiFi.begin(ssid_global, pass_global);
}

bool isWiFiConnected() {
    return (WiFi.status() == WL_CONNECTED);
}

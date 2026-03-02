#include "Audio.h"
#include "WiFi.h"

extern "C" void app_main() {
    initArduino();
    initWiFi();

    // Task Creation 
    xTaskCreate(audioTask, "AudioTask", 8192, NULL, 1, NULL);

    while(1) {
        if (isWiFiConnected()) {
            static bool msgShown = false;
            if (!msgShown) {
                Serial.printf("[WIFI] Connesso! IP: %s\n", WiFi.localIP().toString().c_str());
                msgShown = true;
            }
        } else {
            Serial.println("[WIFI] Ricerca segnale...");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
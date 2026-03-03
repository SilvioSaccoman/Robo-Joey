#include "Audio.h"
#include "WiFiManager.h"

extern "C" void app_main() {
    initArduino();
    initWiFi();

    // Task Creation 
    xTaskCreate(audioTask, "AudioTask", 8192, NULL, 1, NULL);

    while(1) {
        if (isWiFiConnected()) {
            static bool msgShown = false;
            if (!msgShown) {
                ESP_LOGI("WiFi", "Connesso a WiFi: %s", SSID);
                msgShown = true;
            }
        } else {
            ESP_LOGI("WiFi", "Ricerca segnale...");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
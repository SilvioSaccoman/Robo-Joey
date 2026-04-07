#include "Audio.h"
#include "WiFiManager.h"
 #include "MotorControl.h"

extern "C" void app_main() {
    initArduino();
    initWiFi();

    Setup_Motor();

    // Task Creation 
    xTaskCreate(audioTask, "AudioTask", 8192, NULL, 1, NULL);
    xTaskCreatePinnedToCore(udpReceiverTask, "UDPReceiverTask", 4096, NULL, 1, NULL, 1); // Only run on core 1 to avoid conflicts 
    xTaskCreate(inputTask, "InputTask", 4096, NULL, 1, NULL);
    xTaskCreate(motorTask, "MotorTask", 4096, NULL, 1, NULL);

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
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
#include "Audio.h"
#include "WiFiManager.h"
 #include "MotorControl.h"

extern "C" void app_main() {
    initArduino();
    initWiFi();

    Setup_Motor();

    // Task Creation 
    //xTaskCreate(audioTask, "AudioTask", 8192, NULL, 1, NULL);

    stepper.moveTo(32000);

    while(1) {

        stepper.run();

        // if (isWiFiConnected()) {
        //     static bool msgShown = false;
        //     if (!msgShown) {
        //         ESP_LOGI("WiFi", "Connesso a WiFi: %s", SSID);
        //         msgShown = true;
        //     }
        // } else {
        //     ESP_LOGI("WiFi", "Ricerca segnale...");
        // }
        //vTaskDelay(pdMS_TO_TICKS(10));
    }
}
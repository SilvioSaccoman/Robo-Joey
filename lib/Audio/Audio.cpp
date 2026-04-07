#include "Audio.h"

TaskHandle_t audioTaskHandle = NULL; // Global handle for the audio task

void audioTask(void *pvParameters) {
    audioTaskHandle = xTaskGetCurrentTaskHandle(); // Store the task handle for later use

    // Initialize audio components
    AudioGeneratorMP3 *mp3 = new AudioGeneratorMP3();
    AudioFileSourcePROGMEM *file = new AudioFileSourcePROGMEM(HYD_1, sizeof(HYD_1));
    AudioOutputI2S *out = new AudioOutputI2S();
    
    // Setting up I2S output
    out->SetPinout(26, 25, 22); // BCLK, LRCK, DOUT
    out->SetGain(1); // Volume control (0.0 to 1.0)
    
    // Main audio loop
    while(true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait for a notification to start playing

        ESP_LOGI("AUDIO", "How you doin'? Starting audio playback...");

        AudioFileSourcePROGMEM *file = new AudioFileSourcePROGMEM(HYD_1, sizeof(HYD_1));
        mp3->begin(file, out);

        while(mp3->isRunning()) {
            if (!mp3->loop()) {
                mp3->stop();
            }
            // Small delay to prevent watchdog timer resets and allow other tasks to run
            vTaskDelay(1); 
        }

        file->close();
        delete file;
        file = nullptr;
        ESP_LOGI("AUDIO", "Track finished, waiting for next trigger...");
    }
}
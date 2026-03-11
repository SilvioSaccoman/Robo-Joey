#include "Audio.h"

void audioTask(void *pvParameters) {

    // Initialize audio components
    AudioGeneratorMP3 *mp3 = new AudioGeneratorMP3();
    AudioFileSourcePROGMEM *file = new AudioFileSourcePROGMEM(HYD_1, sizeof(HYD_1));
    AudioOutputI2S *out = new AudioOutputI2S();
    
    // Setting up I2S output
    out->SetPinout(26, 25, 22); // BCLK, LRCK, DOUT
    out->SetGain(3.5); // Volume control (0.0 to 1.0)
    mp3->begin(file, out);

    // Main audio loop
    while(true) {
        if (mp3->isRunning()) { // If the MP3 is still playing, keep it going
            if (!mp3->loop()) mp3->stop(); // If loop returns false, the track has ended
        } else {
            vTaskDelay(pdMS_TO_TICKS(100));
        }vTaskDelay(1); 
    }
}
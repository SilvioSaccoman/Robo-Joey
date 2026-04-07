#include "InputManager.h"

static ControlPacket lastValidCommand = {0, 0};
static uint32_t lastReceptionTime = 0;

void processInput(ControlPacket packet) {
    lastValidCommand = packet;
    lastReceptionTime = millis();
}

static bool audioTriggered = false;
static uint32_t lastAudioTime = 0;
const uint32_t AUDIO_COOLDOWN = 3000; // 3 seconds

void inputTask(void *pvParameters) {
    static uint8_t lastLoggedCommand = 99;
    while (1) {
        // Watchdog: se non ricevo pacchetti da più di 300ms, fermo tutto
        if (millis() - lastReceptionTime > 300) {
            //ESP_LOGW("INPUT", "Nessun comando ricevuto da 300ms, fermo i motori");
            //Stop_Motor();
        } else {
            // Applica la logica in base al comando
            switch (lastValidCommand.command) {
                case STOP_MOTOR: 
                    audioTriggered = false; // Reset audio trigger when stopping
                    Stop_Motor(); 
                break;
                case MOVE_FORWARD: 
                    Move_Forward();  
                break;
                case MOVE_BACKWARD: 
                    Move_Backward(); 
                    break;
                case TURN_RIGHT: 
                    Turn_Right();    
                    break;
                case TURN_LEFT: 
                    Turn_Left();     
                    break;
                case TRIGGER_AUDIO_TASK: 
                    
                    if (!audioTriggered && (millis() - lastAudioTime > AUDIO_COOLDOWN)) {
                        ESP_LOGI("INPUT", "How you doin'?");
                        if (audioTaskHandle != NULL) {
                            xTaskNotifyGive(audioTaskHandle); // Wake up the audio task to play the sound
                        }
                        audioTriggered = true;
                        lastAudioTime = millis();
                    }
            
                    break;
                default: 
                    ESP_LOGW("INPUT", "Comando sconosciuto: %d", lastValidCommand.command);
                    //Stop_Motor();   
                    break;
            }
        }

        if (lastValidCommand.command != lastLoggedCommand) {
            ESP_LOGI("INPUT", "Nuovo stato: %d", lastValidCommand.command);
            lastLoggedCommand = lastValidCommand.command;
        }

        vTaskDelay(pdMS_TO_TICKS(20)); // Frequenza di aggiornamento motori
    }
}
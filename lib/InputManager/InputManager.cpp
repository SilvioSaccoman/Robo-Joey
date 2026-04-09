#include "InputManager.h"

static ControlPacket lastValidCommand = {0, 0};
static uint8_t previousCommand = 99; // Stores the penultly received command
static uint32_t lastReceptionTime = 0;

// Global multiplier for dynamic speed scaling
float speedMultiplier = 0.25f; 

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
        // Watchdog: if no packets received for > 500ms, stop and reset multiplier
        if (millis() - lastReceptionTime > 500) {
            speedMultiplier = 0.25f;
            Stop_Motor();
        } else {
            
            // Multiplier Logic
            if (lastValidCommand.command != STOP_MOTOR) {
                // Increment the multiplier gradually up to 1.0 for smoother acceleration
                if (speedMultiplier < 1.0f) {
                    speedMultiplier += 0.015f; // 1 second to reach the max speed
                }
            }

            // Reset multiplier if a new command is received that is different from the previous one
            if (lastValidCommand.command != previousCommand) {
                speedMultiplier = 0.25f; 
                previousCommand = lastValidCommand.command;
            }

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
                            xTaskNotifyGive(audioTaskHandle); // Wake up audio task
                        }
                        audioTriggered = true;
                        lastAudioTime = millis();
                    }
                break;

                default: 
                    ESP_LOGW("INPUT", "Unknown command: %d", lastValidCommand.command);
                break;
            }
        }

        if (lastValidCommand.command != lastLoggedCommand) {
            ESP_LOGI("INPUT", "Cmd: %d | Multiplier: %.2f", lastValidCommand.command, speedMultiplier);
            lastLoggedCommand = lastValidCommand.command;
        }

        vTaskDelay(pdMS_TO_TICKS(20)); // Motor update frequency
    }
}
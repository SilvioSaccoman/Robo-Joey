/**
 * @file InputManager.h
 */
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <cstdint>
#include "MotorControl.h"
#include "esp_log.h"
#include "Arduino.h" 
#include "Audio.h"

/**
 * Command types that the robot can receive
 */
enum CommandType : uint8_t {
    STOP_MOTOR = 0,
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 2,
    TURN_RIGHT = 3,
    TURN_LEFT = 4,
    TRIGGER_AUDIO_TASK = 5
};

/**
 * Structure to hold the control information received via UDP
 */
struct __attribute__((packed)) ControlPacket {
    uint8_t command;      // Type of command (e.g., MOVE_FORWARD, TURN_LEFT, etc.)
    int32_t time_stamp;   // Timestamp 
};

/**
 * Process a received ControlPacket and update the robot's state accordingly
 */
void processInput(ControlPacket packet);

/*
 * Task function to handle input processing
 */
void inputTask(void *pvParameters);

#endif // INPUT_MANAGER_H
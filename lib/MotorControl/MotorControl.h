#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "Arduino.h"
#include <AccelStepper.h>

extern float speedMultiplier; // Global multiplier for dynamic speed scaling

// LEFT MOTOR
#define STEP_L 14
#define DIR_L 12

// RIGHT MOTOR
#define STEP_R 27
#define DIR_R 13

// Speed settings
#define max_speed 3000 // 150 RPM 
#define acceleration 2000 // Acceleration in steps/s^2

extern AccelStepper stepperL;
extern AccelStepper stepperR;

/**
 * Setup function to initialize motor parameters such as max speed and acceleration.
 */
void Setup_Motor();

/**
 * Function to move the robot forward.
 */
void Move_Forward();

/**
 * Function to move the robot backward.
 */
void Move_Backward();

/**
 * Function to turn the robot to the right.
 */
void Turn_Right();

/**
 * Function to turn the robot to the left.
 */
void Turn_Left();

/**
 * Function to stop both motors immediately.
 */
void Stop_Motor();

/**
 * Task function to continuously run the motors at their set speeds.
 * This should be run in a FreeRTOS task to ensure smooth motor control.
 */
void motorTask(void *pvParameters); 

#endif // MOTORCONTROL_H
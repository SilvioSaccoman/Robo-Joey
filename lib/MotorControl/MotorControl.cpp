#include "MotorControl.h"

// Definition of the stepper motor objects
AccelStepper stepperL(1, STEP_L, DIR_L); 
AccelStepper stepperR(1, STEP_R, DIR_R);

void Setup_Motor(){
    stepperL.setMaxSpeed(max_speed); 
    stepperL.setAcceleration(acceleration); 
    stepperR.setMaxSpeed(max_speed); 
    stepperR.setAcceleration(acceleration); 
}

void Move_Forward() {
    stepperL.setSpeed(max_speed*speedMultiplier); 
    stepperR.setSpeed(-max_speed*speedMultiplier); 
}

void Move_Backward() {
    stepperL.setSpeed(-max_speed*speedMultiplier);
    stepperR.setSpeed(max_speed*speedMultiplier);
}

void Turn_Right() {
    // Left motor forward, right motor less forward for a right turn
    stepperL.setSpeed(max_speed*speedMultiplier);
    stepperR.setSpeed(max_speed*speedMultiplier);
}

void Turn_Left() {
    // Left motor less forward, right motor forward for a left turn
    stepperL.setSpeed(-max_speed*speedMultiplier);
    stepperR.setSpeed(-max_speed*speedMultiplier);
}

void Stop_Motor() {
    stepperL.setSpeed(0);
    stepperR.setSpeed(0);
}

void motorTask(void *pvParameters) {
    while (1) {
        stepperL.runSpeed();
        stepperR.runSpeed();

        taskYIELD();
    }
}
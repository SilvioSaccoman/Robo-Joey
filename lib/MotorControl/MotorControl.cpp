#include "MotorControl.h"

AccelStepper stepper(1, STEPPIN, DIRPIN); // Create an instance of AccelStepper with DRIVER interface (1)

void Setup_Motor(){
    stepper.setMaxSpeed(5200); // Set maximum speed (steps per second) --> 100 RPM
    stepper.setAcceleration(200); // Set acceleration (steps per second^2)
}
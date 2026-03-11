#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "Arduino.h"
#include <AccelStepper.h>

#define STEPPIN 14
#define DIRPIN 27

extern AccelStepper stepper;

void Setup_Motor();

#endif // MOTORCONTROL_H
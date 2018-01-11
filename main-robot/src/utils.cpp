#include "utils.hpp"
#include "API.h"
#include <math.h>

//////////////////////////////////////////////////////////////////
// PIDCONTROLLER CLASS
//////////////////////////////////////////////////////////////////
PIDController::PIDController(float kP, float kI, float kD, float target, float threshold, bool reverseI)
  : kP(kP)
  , kI(kI)
  , kD(kD)
  , target(target)
  , threshold(threshold)
  , reverseI(reverseI)
  , lastP(target)
{}

float PIDController::getOutput(float input)
{
    float D = (target-input) - lastP;
    float P = target - input;

    if (!reverseI)
      if (abs(input - target) < threshold)
        I = P + I;
      else
        I = 0;
    else
      if (abs(input - target) > threshold)
        I = P + I;
      else
        I = 0;

    lastP = P;

    return kP * P + kI * I + kD * D;
}

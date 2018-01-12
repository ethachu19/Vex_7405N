#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "io.hpp"
#include "motor.hpp"
#include "sensors.hpp"
#include "userInterface.hpp"
#include "utils.hpp"

class Robot {
public:
  void driveForward(int power, float dist);
private:
  float wheelDiameter;
  float cmPerEnc;
};

extern Robot robot;

extern SyncedMotors leftDrive;
extern SyncedMotors rightDrive;
extern Motor chainbar;
extern Motor intake;
extern Motor mobileGoalLift;
extern Motor leftLift;
extern Motor rightLift;
extern Potentiometer chainbarPot;
extern Potentiometer leftLiftPot;
extern Potentiometer rightLiftPot;
extern Gyroscope gyro;

#endif

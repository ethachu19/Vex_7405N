#include "robot.hpp"
#include "io.hpp"
#include "motor.hpp"
#include "sensors.hpp"
#include "userInterface.hpp"
#include "utils.hpp"

Robot robot = Robot();

SyncedMotors leftDrive = SyncedMotors(Motor(5), Motor(7));
SyncedMotors rightDrive = SyncedMotors(Motor(2), Motor(8));
Motor chainbar = Motor(9);
Motor intake = Motor(4);
Motor mobileGoalLift = Motor(10);
Motor leftLift = Motor(3);
Motor rightLift = Motor(6);
Potentiometer chainbarPot = Potentiometer(4);
Potentiometer leftLiftPot = Potentiometer(2);
Potentiometer rightLiftPot = Potentiometer(1);
Gyroscope gyro = Gyroscope(3);

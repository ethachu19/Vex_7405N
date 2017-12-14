/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {

  gyroReset(gyro);
  resetIMEs();

  //set motor to move forward
  chassisSet(127, 127);

  //wait until imes rotate a certain amount moving forward
  waitForIMEs(1750, straight, true);

  //stop once the IMEs have reached the right amount of rotations
  chassisSet(0, 0);


  //bring mobile goal lift back
  mobileSet(-127);

  //wait until lift moves back
  delay(900);

  //stop mobile goal when in the right position
  mobileSet(0);







  //set motor to turn to the left
  chassisSet(-127, 127);

  //wait until gyros have reached 180 degrees
  waitForGyro(180, left);

  //stop motors
  chassisSet(0, 0);

  //set motor to move forward
  chassisSet(127, 127);

  //wait until imes rotate a certain amount moving forward
  waitForIMEs(1000, straight, false);

  //stop once the IMEs have reached the right amount of rotations
  chassisSet(0, 0);

}

/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#define LEFT_DRIVE 2
#define RIGHT_DRIVE 4 //needs to be reversed
#define LEFT_LIFT_MOTOR 3
#define RIGHT_LIFT_MOTOR 6 //needs to be reversed
#define CLAW 7
#define CHAINBAR 5
#define MOBILE_LIFT 8
#define RIGHT_LIFT_POT 1
#define LEFT_LIFT_POT 2

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void chassisSet(int left, int right);
void moveDrive(int forwardMotion, int sideMotion);
int c = 0;

void operatorControl() {
	while (1) {

		//base speed for the right side of the lift
		int upSpeedRight = 110;

		//base speed for the left side of the lift
		int upSpeedLeft = -110;

		//get petentiometer values from the right lift potentiometer
		int rLiftPot = abs(analogReadCalibrated(1));

		//get potentiomemter values from the left lift potentiometer
		int lLiftPot = abs(analogReadCalibrated(2));



		//positive = forwards, negative = backwards
		int forwardMotion = joystickGetAnalog(1, 3);

		//positive = right, negative = left
		int sideMotion = joystickGetAnalog(1, 1);





		//Syncing lift speeds for left and right side using potentiometers
		if(rLiftPot < (lLiftPot - 100)){
				upSpeedLeft = 60 ;
				upSpeedRight = -115;
			}else if(lLiftPot < (rLiftPot - 100 )){
				upSpeedRight = -60;
				upSpeedLeft = 115;
			}else {
				upSpeedRight = -110;
				upSpeedLeft = 110;
			}

			//Tele op Lift controls
			if(joystickGetDigital(1, 8, JOY_UP)){ //lift comes up on button click
				motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
				motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
				c = 1;
			}else if(joystickGetDigital(1, 8, JOY_DOWN)){ //lift goes down on button click
				c = 0;
				motorSet(LEFT_LIFT_MOTOR, 5);
				motorSet(RIGHT_LIFT_MOTOR, -5);
				c = 1;
			}else if(c == 1){
				motorSet(LEFT_LIFT_MOTOR, 30); //hold power while the button is not being pressed
				motorSet(RIGHT_LIFT_MOTOR, -30);

			}else {
				motorSet(LEFT_LIFT_MOTOR, 8); //hold power while the button is not being pressed
				motorSet(RIGHT_LIFT_MOTOR, -8);

			}
			if(joystickGetDigital(1, 6, JOY_UP)){ //resets the hold power
				c = 0;
			}

			//Beggening of chainbar code
			if(joystickGetDigital(1, 7, JOY_RIGHT)){
			 motorSet(CHAINBAR, 70);
			}else if(joystickGetDigital(1, 7 , JOY_LEFT)){
			 motorSet(CHAINBAR, -50);
			}else {
				 motorSet(CHAINBAR, 0);
			 }

			 //beginning of the Claw code

			if(joystickGetDigital(1, 8, JOY_LEFT)){
				motorSet(CLAW, -30);
			}else if(joystickGetDigital(1, 8 , JOY_RIGHT)){
				motorSet(CLAW, 30);
			}else {
					motorSet(CLAW, 0);
				}



			//prints out the potentiometer values and the corresponding speeds




		//input gathered, move bot
		moveDrive(forwardMotion, sideMotion);



		//print out values
		printf("%d", forwardMotion);
		printf("%s", "\n");
		printf("%d", sideMotion);
		printf("%s", "\n\n");




		delay(100);
	}
}


void chassisSet(int left, int right) {
	motorSet(LEFT_DRIVE, left);

	//right is opposite because that's how we built our robot
	motorSet(RIGHT_DRIVE, -right);
}


void moveDrive(int forwardMotion, int sideMotion) {

	//if the right joystick is being used
	if(sideMotion != 0) {
		//set motors to opposites in order to turn sharply
		chassisSet(sideMotion, -sideMotion);
	}
	//if the left joystick is being used and the right one isn't
	else if(forwardMotion != 0) {
		//set both motors to power equal to the joystick input
		chassisSet(forwardMotion, forwardMotion);
	}
	//if no joysticks are being used
	else {
		//set the chassis to stop moving
		chassisSet(0, 0);
	}
}
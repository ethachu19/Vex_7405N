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

#define LEFT_DRIVE 5
#define RIGHT_DRIVE 2 //needs to be reversed
#define LEFT_LIFT_MOTOR 3
#define RIGHT_LIFT_MOTOR 6 //needs to be reversed
#define CLAW 4
#define CHAINBAR 9
#define MOBILE_LIFT 10
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

int autoCount = 0;

int chainbarBreak = 0;

int chainbarHold = 0;

int chainbar = 0;

int c = 0;

int b = 0;

int autoStackBreaker = 0;
int autoStackCounter = 0;


void operatorControl() {

    encoderReset(encoder);

    while (1) {










        //base speed for the right side of the lift
        int upSpeedRight = 125;

        //base speed for the left side of the lift
        int upSpeedLeft = -125;

        //get petentiometer values from the right lift potentiometer
        int rLiftPot = abs(analogReadCalibrated(1));

        //get potentiomemter values from the left lift potentiometer
        int lLiftPot = abs(analogReadCalibrated(2));

        //positive = forwards, negative = backwards
        int forwardMotion = joystickGetAnalog(1, 3);

        //positive = right, negative = left
        int sideMotion = joystickGetAnalog(1, 1);
        //





        //Syncing lift speeds for left and right side using potentiometers
        if (rLiftPot < (lLiftPot - 50)) {
            upSpeedLeft = -60;
            upSpeedRight = 125;
        } else if (lLiftPot < (rLiftPot - 50)) {
            upSpeedRight = 60;
            upSpeedLeft = -125;
        } else {
            upSpeedRight = 125;
            upSpeedLeft = -125;
        }

        //Tele op Lift controls
        if (joystickGetDigital(1, 8, JOY_UP)) { //lift comes up on button click
            motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
            motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
            c = 1;
        } else if (joystickGetDigital(1, 8, JOY_DOWN)) { //lift goes down on button click
            c = 0;
            motorSet(LEFT_LIFT_MOTOR, 40);
            motorSet(RIGHT_LIFT_MOTOR, -40);
            c = 2;
        } else if (c == 1) {
            motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
            motorSet(RIGHT_LIFT_MOTOR, 20);

        } else if (c == 2) {
            motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
            motorSet(RIGHT_LIFT_MOTOR, 20);

        } else {
            motorSet(LEFT_LIFT_MOTOR, 8); //hold power while the button is not being pressed
            motorSet(RIGHT_LIFT_MOTOR, -8);

        }
        if (joystickGetDigital(1, 6, JOY_UP)) { //resets the hold power
            motorSet(LEFT_LIFT_MOTOR, 0); //hold power while the button is not being pressed
            motorSet(RIGHT_LIFT_MOTOR, -0);

        }

        //chainbar tele op control



        //end of chainbar code




        //Start of Intake code
        if (joystickGetDigital(1, 7, JOY_UP)) {
            motorSet(CLAW, -127);
        } else if (joystickGetDigital(1, 7, JOY_DOWN)) {
            motorSet(CLAW, 50);
        } else {
            motorSet(CLAW, 0);
        }

        //end of intake code



        //start of mobile goal code

        if (joystickGetDigital(1, 7, JOY_RIGHT)) {
            motorSet(MOBILE_LIFT, -127);
        } else if (joystickGetDigital(1, 7, JOY_LEFT)) {
            motorSet(MOBILE_LIFT, 127);
        } else {
            motorSet(10, 0);
        }

        //end of mobile goal code




        //autoStack joyStick controls
        if (joystickGetDigital(1, 5, JOY_UP)) {
            autoStack();
            autoStackCounter++;
        }else if (joystickGetDigital(1, 5, JOY_DOWN)){
            autoStackCounter = 0;
        }


        //input gathered, move botn
        moveDrive(forwardMotion, sideMotion);


        delay(20);
    }
}


void chassisSet(int left, int right) {
    motorSet(LEFT_DRIVE, left);

    //right is opposite because that's how we built our robot
    motorSet(RIGHT_DRIVE, -right);
}

//function for moving the drive
void moveDrive(int forwardMotion, int sideMotion) {

    //if the right joystick is being used
    if (sideMotion != 0) {
        //set motors to opposites in order to turn sharply
        chassisSet(sideMotion, -sideMotion);
    }
        //if the left joystick is being used and the right one isn't
    else if (forwardMotion != 0) {
        //set both motors to power equal to the joystick input
        chassisSet(forwardMotion, forwardMotion);
    }
        //if no joysticks are being used
    else {
        //set the chassis to stop moving
        chassisSet(0, 0);
    }
}


//function that lifts the chainbar to a certain height that is indicated by potentiometer values.
void chainbarMove(int position) { //takes in the desired position of the chainbar
    if(analogRead(4) > position){
      while(analogRead(4) > position) {
        motorSet(CHAINBAR, 127);
      }
    } else if (analogRead(4) < position){
        while(analogRead(4) < position) {
          motorSet(CHAINBAR, -127);
        }
      }

      motorSet(CHAINBAR, 0);
}


//intake function for the auton

void intakeMove(int direction) {
    if (direction == 1) {
        motorSet(CLAW, 127);
    } else if (direction == -1) {
        motorSet(CLAW, -127);
    } else if (direction == 0) {
        motorSet(CLAW, 15);
    }
}

//

//function that lifts the lift to a certain height that is indicated by potentiometer values.
void liftMove(int position) {
    int c = 1;


    //base speed for the right side of the lift
    int upSpeedRight = 125;

    //base speed for the left side of the lift
    int upSpeedLeft = -125;

    //get petentiometer values from the right lift potentiometer
    int rLiftPot = abs(analogReadCalibrated(1));

    //get potentiomemter values from the left lift potentiometer
    int lLiftPot = abs(analogReadCalibrated(2));

    //syncing both sides of the lift while going up

    while (c == 1) {

        if (rLiftPot < (lLiftPot - 100)) {
            upSpeedLeft = -60;
            upSpeedRight = 125;
        } else if (lLiftPot < (rLiftPot - 100)) {
            upSpeedRight = 60;
            upSpeedLeft = -125;
        } else {
            upSpeedRight = 125;
            upSpeedLeft = -125;
        }


        if (abs(analogReadCalibrated(1)) > position) { //checks if the current position is less than the lift height
            while ((abs(analogReadCalibrated(1)) > (position ))) {
                motorSet(LEFT_LIFT_MOTOR, 15);
                motorSet(RIGHT_LIFT_MOTOR, -15);

            }
            c = 0;
        } else if (abs(analogReadCalibrated(1)) < position) { //checks in the current position is more than the lift height
            while ((abs(analogReadCalibrated(1)) < (position))) { // runs the code inside of the while loop until the values are close to that of the desired
                motorSet(LEFT_LIFT_MOTOR, upSpeedLeft);
                motorSet(RIGHT_LIFT_MOTOR, upSpeedRight);
            }
            c = 0;

        }
    }

    motorSet(LEFT_LIFT_MOTOR, 0);
    motorSet(RIGHT_LIFT_MOTOR, 0);



}


//autoStack function
void autoStack() {

        int  liftHeight = 0;
        int chainbarHeight = 1676;

          if (autoStackCounter == 1) {
            liftHeight = 150;
            chainbarHeight = 1600;

        } else if (autoStackCounter == 2) {
            liftHeight = 200;
            chainbarHeight = 1630;
        } else if (autoStackCounter == 3) {
            liftHeight = 400;
        } else if (autoStackCounter == 4) {
            liftHeight = 550;
        } else if (autoStackCounter == 5) {
            liftHeight = 950;
        } else if (autoStackCounter == 6) {
            liftHeight = 1100;
        }



        motorSet(CLAW, 60);
        delay(500);
        motorSet(CLAW, 30);
        printf("%s \n", "intake");
        chainbarMove(2400);
        if(liftHeight > 0){
          liftMove(70);
          motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
          motorSet(RIGHT_LIFT_MOTOR, 20);
          delay(150);
        }

        chainbarMove(chainbarHeight);
        liftMove(liftHeight);
        motorSet(LEFT_LIFT_MOTOR, -20); //hold power while the button is not being pressed
        motorSet(RIGHT_LIFT_MOTOR, 20);
        delay(100);
        motorSet(CLAW, -60);
        delay(400);
        motorSet(CLAW, 0);
        chainbarMove(1900);
        liftMove(0);
        motorSet(LEFT_LIFT_MOTOR, 0);
        motorSet(RIGHT_LIFT_MOTOR, 0);




}

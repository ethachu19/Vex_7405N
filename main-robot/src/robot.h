#pragma once
#include "API.h"

class Motor {
public:
  Motor(unsigned char port, bool reversed = false):
    port(port),
    reversed(reversed),
    encoder(NULL) {}

private:
  unsigned char port;
  bool reversed;
  Encoder encoder;
};

class Robot {
public:
  void driveForward(int power, float dist);
private:
  float wheelDiameter;
  float cmPerEnc;

};

extern Robot robot;

const int LEFT_DRIVE = 5;
const int RIGHT_DRIVE = 2; //needs to be reversed
const int LEFT_LIFT_MOTOR = 3;
const int RIGHT_LIFT_MOTOR = 6; //needs to be reversed
const int CLAW = 4;
const int CHAINBAR = 9;
const int MOBILE_LIFT = 10;
const int RIGHT_LIFT_POT = 1;
const int LEFT_LIFT_POT = 2;

const int LEFT_IME = 0;
const int RIGHT_IME = 2;

#ifndef __UTILS_H__
#define __UTILS_H__

class PIDController {
public:
  PIDController(float kP, float kI, float kD, float target, float threshold = 0, bool reverseI = false);
  float getOutput(float input);
private:
  float kP;
  float kI;
  float kD;
  float I;
  float target;
  float threshold;
  bool reverseI;
  float lastP;
};

class Thread
{
public:
private:
};

#endif

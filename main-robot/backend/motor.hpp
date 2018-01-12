#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "API.h"
#include <vector>

class Motor
{
public:
  Motor(unsigned char port, bool reversed = false);
  void setPower(int speed);
  int getPower();
private:
  unsigned char port;
  bool reversed;
};

class SyncedMotors
{
public:
  SyncedMotors(Motor master, Motor slave);
  void setPower(int speed);
  int getPower();
private:
  Motor master;
  Motor slaves;
};

class MotorEncoder
{
public:
  virtual void initialize() = 0;
  virtual int getPosition() = 0;
  virtual void resetEncoder() = 0;
  virtual void shutdown() = 0;
};

class QuadratureEncoder : public MotorEncoder
{
public:
  QuadratureEncoder(unsigned char topPort, unsigned char bottomPort, bool reversed = false);
  void initialize();
  int getPosition();
  void resetEncoder();
  void shutdown();
private:
  unsigned char topPort;
  unsigned char bottomPort;
  bool reversed;
  Encoder enc;
};

class InternalMotorEncoder : public MotorEncoder
{
public:
  InternalMotorEncoder(unsigned char address, float countsPerRev, bool reversed = false);
  void initialize();
  int getPosition();
  float getPositionRev();
  int getVelocity();
  void resetEncoder();
  void shutdown();
  bool isRunning();
private:
  static void initializeAll();
  static void shutdownAll();
  unsigned char address;
  float countsPerRev;
  bool reversed;
  bool running;
  static bool initialized;
  static int totalIMEs;
};

#endif

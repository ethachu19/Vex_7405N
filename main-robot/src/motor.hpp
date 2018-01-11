#include "API.h"

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

  Encoder enc;
private:
  unsigned char topPort;
  unsigned char bottomPort;
  bool reversed;
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

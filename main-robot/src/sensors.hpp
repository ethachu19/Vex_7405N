#include "io.hpp"
#include "API.h"

typedef AnalogInput Potentiometer;
typedef AnalogInput LightSensor;

class Gyroscope {
public:
  Gyroscope(unsigned char port, unsigned short multiplier = 0);
  void initialize();
  int getValue();
  void reset();
  void shutdown();
private:
unsigned char port;
unsigned short multiplier;
Gyro gyro;
};

class Accelerometer {
public:
  Accelerometer(unsigned char portX, unsigned char portY, unsigned char portZ);
  void initialize();
  void calibrateX();
  void calibrateY();
  void calibrateZ();
  void calibrateAll();
  int getValueX();
  int getValueY();
  int getValueZ();
  int getRawValueX();
  int getRawValueY();
  int getRawValueZ();
private:
  AnalogInput sensorX;
  AnalogInput sensorY;
  AnalogInput sensorZ;
};

class UltrasonicSensor {
public:
  UltrasonicSensor(unsigned char orangePort, unsigned char yellowPort);
  void initialize();
  int getValue();
  void shutdown();
private:
  Ultrasonic sensor;
  unsigned char orangePort;
  unsigned char yellowPort;
};

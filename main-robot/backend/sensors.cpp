#include "sensors.hpp"
#include "API.h"

////////////////////////////////////////////////////
// GYROSCOPE CLASS
////////////////////////////////////////////////////

Gyroscope::Gyroscope(unsigned char port, unsigned short multiplier)
  : port(port)
  , multiplier(multiplier)
  {}

void Gyroscope::initialize()
{
  gyro = gyroInit(port, multiplier);
}

int Gyroscope::getValue()
{
  return gyroGet(gyro);
}

void Gyroscope::reset()
{
  gyroReset(gyro);
}

void Gyroscope::shutdown()
{
  gyroShutdown(gyro);
}

/////////////////////////////////////////////////////////////////////////
// ACCELEROMETER CLASS
/////////////////////////////////////////////////////////////////////////

Accelerometer::Accelerometer(unsigned char portX, unsigned char portY, unsigned char portZ)
 : sensorX(AnalogInput(portX))
 , sensorY(AnalogInput(portY))
 , sensorZ(AnalogInput(portZ))
{}

void Accelerometer::initialize()
{
  sensorX.initialiaze();
  sensorY.initialiaze();
  sensorZ.initialiaze();
}

void Accelerometer::calibrateX()
{
  sensorX.calibrate();
}

void Accelerometer::calibrateY()
{
  sensorY.calibrate();
}

void Accelerometer::calibrateZ()
{
  sensorZ.calibrate();
}

void Accelerometer::calibrateAll()
{
  calibrateX();
  calibrateY();
  calibrateZ();
}

int Accelerometer::getValueX()
{
  return sensorX.getCalibratedValueHR();
}

int Accelerometer::getValueY()
{
  return sensorY.getCalibratedValueHR();
}

int Accelerometer::getValueZ()
{
  return sensorZ.getCalibratedValueHR();
}

int Accelerometer::getRawValueX()
{
  return sensorX.getRawValue();
}

int Accelerometer::getRawValueY()
{
  return sensorY.getRawValue();
}

int Accelerometer::getRawValueZ()
{
  return sensorZ.getRawValue();
}

/////////////////////////////////////////////////////////////////////////
// ULTRASONIC CLASS
/////////////////////////////////////////////////////////////////////////

UltrasonicSensor::UltrasonicSensor(unsigned char orangePort, unsigned char yellowPort)
  : orangePort(orangePort)
  , yellowPort(yellowPort)
{}

void UltrasonicSensor::initialize()
{
  sensor = ultrasonicInit(orangePort, yellowPort);
}

int UltrasonicSensor::getValue()
{
  return ultrasonicGet(sensor);
}

void UltrasonicSensor::shutdown()
{
  ultrasonicShutdown(sensor);
}

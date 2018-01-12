#include "API.h"
#include "io.hpp"

////////////////////////////////////////////////////////////////////
// ANALOG INPUT CLASS
////////////////////////////////////////////////////////////////////
AnalogInput::AnalogInput(unsigned char port)
  : port(port)
  {}

void AnalogInput::initialize()
{
  pinMode(port, INPUT_ANALOG);
}

void AnalogInput::calibrate()
{
    this->calibrationOffset = analogCalibrate(port);
}

int AnalogInput::getRawValue()
{
  return analogRead(port);
}

int AnalogInput::getCalibratedValue()
{
  return analogReadCalibrated(port);
}

int AnalogInput::getCalibratedValueHR()
{
  return analogReadCalibratedHR(port);
}

////////////////////////////////////////////////////////////////////
// DIGITAL INPUT CLASS
////////////////////////////////////////////////////////////////////

DigitalInput::DigitalInput(unsigned char port)
  : port(port)
  {}

void DigitalInput::initialize()
{
  pinMode(port, INPUT);
}

bool DigitalInput::getValue()
{
  return digitalRead(port);
}

//////////////////////////////////////////////////////////////////////
// DIGITAL OUTPUT CLASS
//////////////////////////////////////////////////////////////////////

DigitalOutput::DigitalOutput(unsigned char port)
  : port(port)
  {}

void DigitalOutput::initailize()
{
  pinMode(port, OUTPUT);
}

void DigitalOutput::writeValue(int val)
{
  digitalWrite(port, val);
}

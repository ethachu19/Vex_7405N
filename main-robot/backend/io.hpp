#ifndef __IO_H__
#define __IO_H__

class AnalogInput
{
public:
  AnalogInput(unsigned char port);
  void initialize();
  void calibrate();
  int getRawValue();
  int getCalibratedValue();
  int getCalibratedValueHR();
private:
  unsigned char port;
  int calibrationOffset;
};

class DigitalInput
{
public:
  DigitalInput(unsigned char port);
  void initialize();
  bool getValue();
private:
  unsigned char port;
};

class DigitalOutput
{
public:
  DigitalOutput(unsigned char port);
  void initailize();
  void writeValue(int val);
private:
  unsigned char port;
};

#endif

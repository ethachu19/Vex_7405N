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
  virtual int getPosition() = 0;
  virtual void resetEncoder() = 0;
};

class QuadratureEncoder : public MotorEncoder
{
public:
  QuadratureEncoder(unsigned char topPort, unsigned char bottomPort, bool reversed = false);
  void initialize();
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
  void getVelocity();
private:
  unsigned char address;
  bool reversed;
  int offset;
  float countsPerRev;
};

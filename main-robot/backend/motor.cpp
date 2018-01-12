#include "motor.hpp"

////////////////////////////////////////////////////////////////////////////
// MOTOR CLASS
////////////////////////////////////////////////////////////////////////////
Motor::Motor(unsigned char port, bool reversed)
  : port(port)
  , reversed(reversed)
{}

void Motor::setPower(int speed)
{
  motorSet(port, reversed ? speed * -1 : speed);
}

int Motor::getPower()
{
  int power = motorGet(port);
  return reversed ? power * -1 : power;
}

////////////////////////////////////////////////////////////////////////////
// SYNCEDMOTORS CLASS
////////////////////////////////////////////////////////////////////////////

SyncedMotors::SyncedMotors(Motor master, Motor slave)
  : master(master)
  , slaves(slave)
{
}

void SyncedMotors::setPower(int speed)
{
  master.setPower(speed);
  slaves.setPower(speed);
}

int SyncedMotors::getPower()
{
  return master.getPower();
}

////////////////////////////////////////////////////////////////////////////
// QUADRATURE ENCODER CLASS
////////////////////////////////////////////////////////////////////////////

QuadratureEncoder::QuadratureEncoder(unsigned char topPort, unsigned char bottomPort, bool reversed)
  : topPort(topPort)
  , bottomPort(bottomPort)
  , reversed(reversed)
{}

void QuadratureEncoder::initialize()
{
  this->enc = encoderInit(topPort, bottomPort, reversed);
}

int QuadratureEncoder::getPosition()
{
  return encoderGet(enc);
}

void QuadratureEncoder::resetEncoder()
{
  encoderReset(enc);
}

void QuadratureEncoder::shutdown()
{
  encoderShutdown(enc);
}

////////////////////////////////////////////////////////////////////////////
// IME ENCODER CLASS
////////////////////////////////////////////////////////////////////////////

bool InternalMotorEncoder::initialized = false;
int InternalMotorEncoder::totalIMEs = 0;

void InternalMotorEncoder::initializeAll()
{
  InternalMotorEncoder::totalIMEs = imeInitializeAll();
}

void InternalMotorEncoder::shutdownAll()
{
  imeShutdown();
  InternalMotorEncoder::totalIMEs = 0;
  InternalMotorEncoder::initialized = false;
}

InternalMotorEncoder::InternalMotorEncoder(unsigned char address, float countsPerRev, bool reversed)
  : address(address)
  , countsPerRev(countsPerRev)
  , reversed(reversed)
{}

void InternalMotorEncoder::initialize()
{
  if(!initialized)
    InternalMotorEncoder::initializeAll();
  running = true;
}

int InternalMotorEncoder::getPosition()
{
  int pos;
  if (!imeGet(address, &pos))
    running = false;
  return pos;
}

float InternalMotorEncoder::getPositionRev()
{
  return getPosition() / countsPerRev;
}

int InternalMotorEncoder::getVelocity()
{
  int vel;
  if (!imeGetVelocity(address, &vel))
    running = false;
  return vel;
}

void InternalMotorEncoder::resetEncoder()
{
  if (!imeReset(address))
    running = false;
}

void InternalMotorEncoder::shutdown()
{
  InternalMotorEncoder::shutdownAll();
  running = false;
}

bool InternalMotorEncoder::isRunning()
{
  return running;
}

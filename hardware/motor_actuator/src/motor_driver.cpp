#include <motor_actuator/motor_driver.h>
#include <limits>

MotorDriver::MotorDriver()
{
    for(int i = 0; i<NUM_MOTORS; i++)
    {
        motors_[i+1] = hat_.getMotor(i+1);
    }
}

MotorDriver::MotorDriver(int address, const std::vector<bool>& motors) : hat_(AdafruitMotorHAT(address))
{
    for(int i = 0; i<motors.size(); i++)
    {
        if (motors[i])
        {
            motors_[i+1] = hat_.getMotor(i+1);
        }
    }
}

MotorDriver::~MotorDriver()
{
    for(const auto & motor : motors_)
    {
        motor.second->run (kRelease);
    }
}

void MotorDriver::setMotor(int motor, float speed)
{
    try{
        motors_[motor]->setSpeed(convertSpeed(speed));
        motors_[motor]->run(getCommand(speed));
    } catch(...)
    {
        std::stringstream str;
        str<<"Error when trying to set speed to "<<speed<<" for motor "<<motor;
        util_log::error(str.str());
    }
}

Command MotorDriver::getCommand(float speed)
{
    if(util::isEqual(speed, 0.0, TOLLERENCE)) return kBrake;
    return speed<0.0 ? kBackward : kForward;
}

int MotorDriver::convertSpeed(float speed)
{
    return (int)(255 * (std::abs(speed)/std::numeric_limits<float>::max()));
}
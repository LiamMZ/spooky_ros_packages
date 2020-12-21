#include <motor_actuator/motor_driver.h>

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

bool MotorDriver::setMotor(int motor, int speed, Command command)
{
    try{
        motors_[motor]->setSpeed(speed);
        motors_[motor]->run(command);
        return true;
    } catch(...)
    {
        return false;
    }
}
#include <motor_actuator/adafruitmotorhat.h>
#include <unordered_map>

class MotorDriver
{
    public:
        MotorDriver(int address, std::vector<bool> motors);
        bool setMotor(int motor, int speed, AdafruitDCMotor::Command command);
        ~MotorDriver();
    private:
        AdafruitMotorHAT hat_;
        std::unordered_map<int, std::shared_ptr<AdafruitDCMotor>> motors_;
};
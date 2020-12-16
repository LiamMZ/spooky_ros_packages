#include <thread>
#include <chrono>
// #include <motor_actuator/adafruitmotorhat.h>
#include <motor_actuator/motor_driver.h>
#include <motor_actuator/util.h>

int main()
{
    using namespace std::chrono_literals;

    // // connect using the default device address 0x60
    // AdafruitMotorHAT hat;

    // // get the motor connected to port 1
    // if (auto motor { hat.getMotor (4) })
    // {
    //     // speed must be set before running commands
    //     motor->setSpeed (255);

    //     motor->run (AdafruitDCMotor::kForward);
    //     std::this_thread::sleep_for (1s);

    //     motor->run (AdafruitDCMotor::kBackward);
    //     std::this_thread::sleep_for (1s);

    //     // release the motor after use
    //     motor->run (AdafruitDCMotor::kRelease);
    // }
    const std::vector<bool> motors(4, true);
    MotorDriver md(0x6F, motors);

    md.setMotor(1, 255, kForward);
    md.setMotor(2, 255, kForward);
    md.setMotor(3, 255, kForward);
    md.setMotor(4, 255, kForward);
    std::this_thread::sleep_for (1s);
    
    return 0;
}
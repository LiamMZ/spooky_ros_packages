#include <motor_actuator/adafruitmotorhat.h>
#include <unordered_map>
#include <motor_actuator/util.h>

#define NUM_MOTORS 4

class MotorDriver
{
    public:
        /**
         * Consructor, loads motors into map based on passed boolean values
         * 
         * @param[in] address - i2c address of motor hat
         * @param[in] motors - one hot array of motors indicating which motors are in use
         */
        MotorDriver(int address, const std::vector<bool>& motors);

        /**
         * Default Constructor
         */
        MotorDriver();

        /**
         * Destructor, releases motors if not released already
         */
        ~MotorDriver();
        /**
         * Function to set the action of a motor
         * 
         * @param[in] motor - motor id for motor you wish to command
         * @param[in] speed - the desired speed for the indicated motor 0-255
         * @param[in] command - the command for the given motor in [kforward, kbackward, kBrake, kRelease]
         */
        bool setMotor(int motor, int speed, Command command);

    private:
        /**
         * Handle for the raspi motor hat
         */
        AdafruitMotorHAT hat_;
        /**
         * Map of active motors
         */
        std::unordered_map<int, std::shared_ptr<AdafruitDCMotor>> motors_;
};
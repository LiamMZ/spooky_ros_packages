#include <motor_actuator/adafruitmotorhat.h>
#include <unordered_map>
#include <motor_actuator/util.h>



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
         * @param[in] speed - the desired speed for the indicated motor will be converted to 0-255
         */
        void setMotor(int motor, float speed);


    private:
        /**
         * FUnction to convert a speed from a float to an unsigned int
         * @param[in] speed - speed as a float;
         * @returns speed - speed as an unsigned integer between 0-255
         */
        int convertSpeed(float speed);

        Command getCommand(float speed);
        /**
         * Handle for the raspi motor hat
         */
        AdafruitMotorHAT hat_;
        /**
         * Map of active motors
         */
        std::unordered_map<int, std::shared_ptr<AdafruitDCMotor>> motors_;

        // max difference for isEqual comparison
        const float TOLLERENCE = 0.002;

        // the number of motor outputs on board
        const int NUM_MOTORS = 4;

};
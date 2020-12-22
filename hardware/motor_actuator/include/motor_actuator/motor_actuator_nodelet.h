#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <motor_actuator/motor_driver.h>
#include <spooky_msgs/MotorCommand.h>

namespace motor_actuator
{

    class MotorActuatorNodelet : public nodelet::Nodelet
    {
        public:
            /**
             * Function to initialize nodelet, calls setup function
             */
            virtual void onInit();
            /**
             * Function to set up nodelet, advertises motor command service
             * 
             * @param[in] nh - nodehandle for nodelet
             */
            void Setup(ros::NodeHandle& nh);

        private:
            /**
             * Callback for motor command service
             * 
             * @param[in] req - motor command service request
             * @param[in] res - motor command service response
             * @returns success - indicates command was successfully sent to motor
             */
            bool motor_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res);

            // member variable for motor command service
            ros::ServiceServer motor_server_;
            // member variable for motor driver 
            MotorDriver driver_;
            // member variable for node handle
            ros::NodeHandle nh_;
    };

}
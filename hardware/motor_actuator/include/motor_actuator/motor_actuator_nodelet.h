#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <motor_actuator/motor_driver.h>
#include <std_msgs/Float32.h>


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
            void right_motor_callback(const std_msgs::Float32 cmd);

            void left_motor_callback(const std_msgs::Float32 cmd);



            // member variable for left motor command subscriber
            ros::Subscriber left_motor_sub_;
            // member variable for right motor command subscriber
            ros::Subscriber right_motor_sub_;
            // member variable for motor driver 
            MotorDriver driver_;
            // member variable for node handle
            ros::NodeHandle nh_;
            

            int left_rear_motor_;
            int left_front_motor_;
            int right_rear_motor_;
            int right_front_motor_;
    };

}
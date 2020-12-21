#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <motor_actuator/motor_driver.h>
#include <spooky_msgs/MotorCommand.h>

namespace motor_actuator
{

    class MotorActuatorNodelet : public nodelet::Nodelet
    {
        public:
            virtual void onInit();
            void Setup(ros::NodeHandle& nh);

        private:
            bool motor_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res);

            ros::ServiceServer motor_server_;
            MotorDriver driver_;
            ros::NodeHandle nh_;
    };

}
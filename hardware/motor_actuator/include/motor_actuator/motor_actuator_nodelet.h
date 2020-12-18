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
            bool motor1_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res);
            bool motor2_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res);
            bool motor3_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res);
            bool motor4_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res);
            ros::ServiceServer motor1_server_;
            ros::ServiceServer motor2_server_;
            ros::ServiceServer motor3_server_;
            ros::ServiceServer motor4_server_;
            MotorDriver driver_;
            ros::NodeHandle nh_;
    };

}
#include <motor_actuator/motor_actuator_nodelet.h>
#include <pluginlib/class_list_macros.h>



PLUGINLIB_EXPORT_CLASS(motor_actuator::MotorActuatorNodelet, nodelet::Nodelet)

namespace motor_actuator
{
    void MotorActuatorNodelet::onInit()
    {
        NODELET_DEBUG("Initializing motor driver nodelet...");
        Setup(getNodeHandle());
    }

    void MotorActuatorNodelet::Setup(ros::NodeHandle& nh)
    {
        try
        {
            nh_ = nh; 
            nh.getParam("/motor_actuator/left_rear_motor", left_rear_motor_);
            nh.getParam("/motor_actuator/left_front_motor", left_front_motor_);
            nh.getParam("/motor_actuator/right_rear_motor", right_rear_motor_);
            nh.getParam("/motor_actuator/right_front_motor", right_front_motor_);
            
            left_motor_sub_ = nh.subscribe("lmotor_cmd", 1000, &MotorActuatorNodelet::right_motor_callback, this);
            right_motor_sub_ = nh.subscribe("rmotor_cmd", 1000, &MotorActuatorNodelet::left_motor_callback, this);
        }
        catch(...)
        {
            ROS_ERROR("Failed motor actuator node set up\n");
        }
    }

    void MotorActuatorNodelet::left_motor_callback(const std_msgs::Float32 cmd)
    {
        try
        {
            driver_.setMotor(left_rear_motor_, cmd.data);
            driver_.setMotor(left_front_motor_,cmd.data);
        }
        catch(...)
        {
            ROS_ERROR("Failed to set left motors\n");
        }
    }
    
    void MotorActuatorNodelet::right_motor_callback(const std_msgs::Float32 cmd)
    {
        driver_.setMotor(right_rear_motor_, cmd.data);
        driver_.setMotor(right_front_motor_, cmd.data);
    }
}
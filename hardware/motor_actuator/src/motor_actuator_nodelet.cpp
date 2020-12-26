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
        nh_ = nh; 
        nh.getParam("left_rear_motor", left_rear_motor_);
        nh.getParam("left_front_motor", left_front_motor_);
        nh.getParam("right_rear_motor", right_rear_motor_);
        nh.getParam("right_front_motor", right_front_motor_);
        left_motor_sub_ = nh.subscribe("rmotor_cmd", 1000, &MotorActuatorNodelet::right_motor_callback, this);
        right_motor_sub_ = nh.subscribe("lmotor_cmd", 1000, &MotorActuatorNodelet::left_motor_callback, this);
    }

    void MotorActuatorNodelet::left_motor_callback(const std_msgs::Float32 cmd)
    {
        driver_.setMotor(left_rear_motor_, cmd.data);
        driver_.setMotor(left_front_motor_,cmd.data);
    }
    
    void MotorActuatorNodelet::right_motor_callback(const std_msgs::Float32 cmd)
    {
        driver_.setMotor(right_rear_motor_, cmd.data);
        driver_.setMotor(right_front_motor_, cmd.data);
    }
}